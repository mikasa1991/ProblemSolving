
#define MAX_USER      (1000+10)
#define MAX_TAG       (5000+10)
#define TIME_STR_NUM  (9)
#define STR_NUM       (10)
#define MAX_HASH      (5000+10)
#define MAX_ARR       ((5 * (int)1e5) + 10)
#define MAX_MSG       ((int)1e6 + 10)
#define NULL          (0)
#define MAX_NODE      ((6 * (int)1e5) + 10)
int gFollowTb[MAX_USER][MAX_USER];

// mergeSort buffer
int gArray[MAX_ARR];
int gBuffer[MAX_ARR];

// The below commented functions are for your reference. If you want 
// to use it, uncomment these functions.

int mstrcmp(const char *a, const char *b)
{
    int i;
    for (i = 0; a[i] != '\0'; ++i) if (a[i] != b[i]) return a[i] - b[i];
    return a[i] - b[i];
}

void mstrcpy(char *dest, const char *src)
{
    int i = 0;
    while (src[i] != '\0') { dest[i] = src[i]; i++; }
    dest[i] = src[i];
}

struct Msg
{
    int time;
    int userId;

    void init()
    {
        time = 0;
        userId = 0;
    }
};

Msg gMsgTb[MAX_MSG];

// 최근일수록, userId가 작을수록 우선순위가 높다.
int compare(int a, int b)
{
    int aTime = gMsgTb[a].time;
    int bTime = gMsgTb[b].time;

    if (aTime == bTime)
    {
        return (gMsgTb[a].userId < gMsgTb[b].userId);
    }
    else
    {
        return (aTime > bTime);
    }
}

struct Node
{
    int msgId;
    Node* prev;
    Node* next;
    
    void init()
    {
        msgId = -1;
        prev = NULL;
        next = NULL;
    }

    Node* alloc(int msgId)
    {
        this->msgId = msgId;
        return this;
    }
};

Node gFreeNode[MAX_NODE];
int gUsedCnt;

struct List
{
    Node head;
    Node tail;
    Node* cur;
    int nodeCnt;

    void init()
    {
        cur = head.next;
        nodeCnt = 0;
        head.init();
        tail.init();
        head.next = &tail;
        tail.prev = &head;
    }

    void addNode(int msgId)
    {
        bool bNeedToAdd = true;
        int searchCnt;
        Node* temp;

        // 우선순위가 상위 5개보다 낮으면, node를 추가할 필요가 없다.
        // 그 외는 node를 추가해야한다.
        for (searchCnt = 0, temp = head.next; temp != &tail; temp = temp->next, searchCnt++)
        {
            if (searchCnt > 5)
            {
                bNeedToAdd = false;
                break;
            }
            else
            {
                if (compare(msgId, temp->msgId))
                {
                    break;
                }
            }
        }

        if (true == bNeedToAdd)
        {
            Node* pNode = gFreeNode[gUsedCnt++].alloc(msgId);
            
            pNode->next = temp;
            pNode->prev = temp->prev;
            temp->prev->next = pNode;
            temp->prev = pNode;
            
            nodeCnt++;
        }
    }
};

List gUserListTb[MAX_USER];
List gTagListTb[MAX_TAG];
int gId;

struct hashNode
{
    char key[STR_NUM];
    int data; // id
    hashNode* prev;
    hashNode* next;

    void init()
    {
        data = 0;
        prev = NULL;
        next = NULL;
    }

    hashNode* alloc(char* key, int data)
    {
        mstrcpy(this->key, key);
        this->data = data;
        return this;
    }
};

hashNode gFreeHashNode[MAX_HASH];
int gUsedHashNodeCnt;

struct hashList
{
    hashNode head;
    hashNode tail;
    int nodeCnt;

    void init()
    {
        head.init();
        tail.init();
        head.next = &tail;
        tail.prev = &head;
        nodeCnt = 0;
    }

    int getData(char* str)
    {
        // str이 없으면, add하고 return.
        // str이 있으면, return.
        for (hashNode* temp = head.next; temp != &tail; temp = temp->next)
        {
            if (0 == mstrcmp(temp->key, str)) // str이 있으면, return.
            {
                return temp->data;
            }
        }

        hashNode* pNode = gFreeHashNode[gUsedHashNodeCnt++].alloc(str, gId++);
        pNode->next = head.next;
        pNode->prev = &head;
        head.next->prev = pNode;
        head.next = pNode;
        nodeCnt++;
        
        return pNode->data;
    }
};

hashList gHashListTb[MAX_HASH];

unsigned long hash(const char* str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
    {
        hash = (((hash << 5) + hash) + c) % MAX_HASH;
    }

    return hash % MAX_HASH;
}

void init()
{
    gUsedCnt = 0;
    gId = 0;
    gUsedHashNodeCnt = 0;
    for (int i = 0; i < MAX_MSG; i++)
    {
        gMsgTb[i].init();
    }
    for (int i = 0; i < MAX_USER; i++)
    {
        gUserListTb[i].init();
        gFollowTb[i][0] = 0;
    }
    for (int i = 0; i < MAX_TAG; i++)
    {
        gTagListTb[i].init();
    }
    for (int i = 0; i < MAX_HASH; i++)
    {
        gHashListTb[i].init();
    }
}

#define TIME_NUM (8)
int getTime(char* pTime)
{
    int nTime = 0;
    int a = 100000;
    for (int i = 0; i < TIME_NUM; i++)
    {
        if (':' == pTime[i])
        {
            continue;
        }
        nTime += (pTime[i] - '0') * a;
        a = a / 10;
    }
    return nTime;
}

void copyTag(char* pDest, char* pSrc, int* pIndex)
{
    int i;
    for (i = 0; (' ' != pSrc[i]) && (0 != pSrc[i]); i++)
    {
        pDest[i] = pSrc[i];
    }
    *pIndex += i;
}

void createMessage(int msgID, int userID, char msgData[])
{
    // msgTb
    gMsgTb[msgID].userId = userID;
    gMsgTb[msgID].time = getTime(msgData);

    // userListTb
    gUserListTb[userID].addNode(msgID);

    // hashTagListTb
    int index = TIME_STR_NUM;
    while (0 != msgData[index])
    {
        char string[STR_NUM] = { 0, };
        if (' ' == msgData[index]) index++;
        copyTag(string, msgData + index, &index);

        int h = hash(string);
        int id = gHashListTb[h].getData(string);
        gTagListTb[id].addNode(msgID);
    }
}

void followUser(int userID1, int userID2)
{
    int* pId = &gFollowTb[userID1][0];
    (*pId)++;
    gFollowTb[userID1][*pId] = userID2;
}

int searchByHashtag(char tagName[], int retIDs[])
{
    int h = hash(tagName);
    int id = gHashListTb[h].getData(tagName);
    
    int cnt = 0;
    List* pList = &gTagListTb[id];
    for (Node* temp = pList->head.next; temp != &(pList->tail); temp = temp->next)
    {
        if (cnt < 5)
        {
            retIDs[cnt++] = temp->msgId;
        }
        else
        {
            break;
        }
    }
    return cnt;
}

void mergeSort(int s, int e)
{
    // divide
    int m = (s + e) / 2;
    if (s < e)
    {
        mergeSort(s, m);
        mergeSort(m + 1, e);
    }

    // merge
    int i = s;
    int j = m + 1;
    int k = s;

    while (i <= m && j <= e)
    {
        if (compare(gArray[i], gArray[j])) gBuffer[k++] = gArray[i++];
        else gBuffer[k++] = gArray[j++];
    }

    while (i <= m) gBuffer[k++] = gArray[i++];
    while (j <= e) gBuffer[k++] = gArray[j++];

    for (int i = s; i <= e; i++)
    {
        gArray[i] = gBuffer[i];
    }
}

int getMessages(int userID, int retIDs[])
{
    int c = 0;
    // follow table을 한 바퀴 돈다.
    for (int i = 0; i <= gFollowTb[userID][0]; i++)
    {
        int uId;
        if (0 == i) uId = userID;
        else        uId = gFollowTb[userID][i];

        List* pList = &gUserListTb[uId];
        int cnt = 0;
        for (Node* temp = pList->head.next; temp != &(pList->tail); temp = temp->next)
        {
            if (cnt < 5)
            {
                gArray[c++] = temp->msgId;
                cnt++;
            }
            else
            {
                break;
            }
        }
    }

    mergeSort(0, c-1);

    int cnt = 0;
    for (int i = 0; i < c; i++)
    {
        if (cnt < 5)
        {
            retIDs[i] = gArray[i];
            cnt++;
        }
        else
        {
            break;
        }
    }
    return cnt;
}