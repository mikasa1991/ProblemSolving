// https://out.swexpertacademy.samsung.com/common/swea/solvingPractice/problemDetail.do?contestProbId=AWxQBnaf4YkAAAHb
//#include <assert.h>

#define MAX_USER      1000
#define MAX_TAG       5000

// The below commented functions are for your reference. If you want 
// to use it, uncomment these functions.

int mstrcmp(const char *a, const char *b)
{
    int i;
    for (i = 0; a[i] != '\0'; ++i) if (a[i] != b[i]) return a[i] - b[i];
    return a[i] - b[i];
}

int mstrcpy(char *dest, const char *src)
{
    int i = 0;
    while (src[i] != '\0' && src[i] != ' ') { dest[i] = src[i]; i++; }
    if (src[i] == '\0')
    {
        dest[i] = src[i];
    }
    return i;
}

#define NULL            (0)
#define MAX_MSG_NUM     ((int)1e6+1)
#define MAX_HASHTAG_NUM (10000+1)
#define MAX_USER_NUM    (1000+1)
#define MAX_NODE        ((int)1e7)
#define MAX_HASHTAG_LEN (9 + 1)

struct Msg
{
    int userId;
    int time;

    void init()
    {
        userId = 0;
        time = 0;
    }
};

struct Node
{
    int msgId;
    Node* prev;
    Node* next;

#define NOT_DEFINED (-1)
    void init()
    {
        msgId = NOT_DEFINED;
        prev = NULL;
        next = NULL;
    }

    Node* alloc()
    {
        return this;
    }
};

Node gNodePool[MAX_NODE];
int gUsedCnt;
Msg gMsgTb[MAX_MSG_NUM];

// time이 클수록, time이 같다면 유저 id가 작을수록
int compare(int a, int b)
{
    Msg aMsg;
    Msg bMsg;
    aMsg.time = gMsgTb[a].time;
    aMsg.userId = gMsgTb[a].userId;
    bMsg.time = gMsgTb[b].time;
    bMsg.userId = gMsgTb[b].userId;

    int bRet = 0;
    if (aMsg.time > bMsg.time)
    {
        bRet = 1;
    }
    else if (aMsg.time < bMsg.time)
    {
        bRet = 0;
    }
    else // (aMsg.time == bMsg.time)
    {
        if (aMsg.userId < bMsg.userId)
        {
            bRet = 1;
        }
        else if (aMsg.userId > bMsg.userId)
        {
            bRet = 0;
        }
        else
        {
            //assert(0);
        }
    }
    return bRet;
}

struct List
{
    Node head;
    Node tail;
    int cnt;

    void init()
    {
        cnt = 0;

        head.init();
        tail.init();
        head.next = &tail;
        tail.prev = &head;
    }

    int insertByOrder(int msgId)
    {
        int bRet = 0;

        Node* temp;
        int searchCnt = 0;
        for (temp = head.next; temp != &tail; temp = temp->next, searchCnt++)
        {
            if (searchCnt >= 5) // 나보다 우선순위 높은 노드가 5개 있다면,
            {
                return 0;
            }
            if (compare(msgId, temp->msgId))
            {
                bRet = 1;
                break;
            }
        }

        Node* newNode = gNodePool[gUsedCnt++].alloc();
        newNode->msgId = msgId;
        newNode->next = temp;
        newNode->prev = temp->prev;
        temp->prev->next = newNode;
        temp->prev = newNode;
        cnt++;
        return bRet;
    }
};

List gUserTb[MAX_USER_NUM];

unsigned long hash(const char* str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
    {
        hash = (((hash << 5) + hash) + c) % MAX_HASHTAG_NUM;
    }

    return hash % MAX_HASHTAG_NUM;
}

struct Hash
{
    char key[MAX_HASHTAG_LEN];
    List list;

    void init()
    {
        for (int i = 0; i < MAX_HASHTAG_LEN; i++)
        {
            key[i] = 0;
            list.init();
        }
    }
};
Hash gHashTb[MAX_HASHTAG_NUM];

int find(const char* _key)
{
    unsigned long h = hash(_key);
    int cnt = MAX_HASHTAG_NUM;

    while (gHashTb[h].key[0] != 0 && cnt--)
    {
        if (mstrcmp(gHashTb[h].key, _key) == 0)
        {
            return h;
        }
        h = (h + 1) % MAX_HASHTAG_NUM;
    }
    return -1;
}

int add(const char* _key)
{
    unsigned long h = hash(_key);

    while (gHashTb[h].key[0] != 0)
    {
        if (mstrcmp(gHashTb[h].key, _key) == 0) //기존에 등록된 key라면,
        {
            return h;
        }

        h = (h + 1) % MAX_HASHTAG_NUM;
    }
    mstrcpy(gHashTb[h].key, _key);
    return h;
}
#define MAX_HEAP_SIZE (MAX_USER_NUM * 10)

struct Heap
{
    int heap[MAX_HEAP_SIZE] = { 0, }; //msgId
    int heapSize = 0;

    void init(void)
    {
        heapSize = 0;
    }

    int heapPush(int value)
    {
        if (heapSize + 1 > MAX_HEAP_SIZE)
        {
            return 0;
        }

        heap[heapSize] = value;

        int current = heapSize;
        while (current > 0 && compare(heap[current], heap[(current - 1) / 2]))
        {
            int temp = heap[(current - 1) / 2];
            heap[(current - 1) / 2] = heap[current];
            heap[current] = temp;
            current = (current - 1) / 2;
        }

        heapSize = heapSize + 1;

        return 1;
    }

    int heapPop(int* value)
    {
        if (heapSize <= 0)
        {
            return -1;
        }

        *value = heap[0];
        heapSize = heapSize - 1;

        heap[0] = heap[heapSize];

        int current = 0;
        while (current * 2 + 1 < heapSize)
        {
            int child;
            if (current * 2 + 2 == heapSize)
            {
                child = current * 2 + 1;
            }
            else
            {
                child = compare(heap[current * 2 + 1], heap[current * 2 + 2]) ? current * 2 + 1 : current * 2 + 2;
            }

            if (compare(heap[current], heap[child]))
            {
                break;
            }

            int temp = heap[current];
            heap[current] = heap[child];
            heap[child] = temp;

            current = child;
        }
        return 1;
    }
};

int gFollowTb[MAX_USER_NUM][MAX_USER_NUM];
Heap gHeap;
void init()
{
    gUsedCnt = 0;
    for (int i = 0; i < MAX_MSG_NUM; i++)
    {
        gMsgTb[i].init();
    }
    for (int i = 0; i < MAX_USER_NUM; i++)
    {
        gUserTb[i].init();
    }
    for (int i = 0; i < MAX_HASHTAG_NUM; i++)
    {
        gHashTb[i].init();
    }
    for (int i = 0; i < MAX_USER_NUM; i++)
    {
        for (int j = 0; j < MAX_USER_NUM; j++)
        {
            gFollowTb[i][j] = 0;
        }
    }
    gHeap.init();
}
// msgTb에 userId, time을 등록한다. (hashTag는 굳이...)
// userTb에 Node(msgId)를 우선순위를 고려하여 삽입한다. 최대 5개까지.
// hashtagTb에 Node(msgId)를 우선순위를 고려하여 삽입한다. 최대 5개까지.
void createMessage(int msgID, int userID, char msgData[])
{
    gMsgTb[msgID].userId = userID;

#define TIME_LEN (8)
    int num = 100000;
    int time = 0;
    int i;
    for (i = 0; i < TIME_LEN; i++)
    {
        if (':' == msgData[i]) continue;
        time = time + ((msgData[i]-'0') * num);
        num = num / 10;
    }
    gMsgTb[msgID].time = time;
    gUserTb[userID].insertByOrder(msgID);

    while (NULL != msgData[i])
    {
        if ('#' == msgData[i])
        {
            char string[MAX_HASHTAG_LEN] = { 0, };
            i = i + mstrcpy(string, &msgData[i]);
            int idx = add(string);
            List* list = &gHashTb[idx].list;
            list->insertByOrder(msgID);
        }
        else
        {
            i++;
        }
    }
}

// followTb에 userId1 index에 userId2를 등록한다.
void followUser(int userID1, int userID2)
{
    int* followCntIdx = &gFollowTb[userID1][1000];
    gFollowTb[userID1][*followCntIdx] = userID2;
    (*followCntIdx)++;
}

// hashtagTb에 tagName으로 Index를 찾아서...
int searchByHashtag(char tagName[], int retIDs[])
{
    int idx = find(tagName);
    if (-1 == idx)
    {
        return 0;
    }

    List* list = &gHashTb[idx].list;
    int cnt = 0;
    for (Node* temp = list->head.next; temp != &(list->tail); temp = temp->next)
    {
        if (cnt >= 5) break;
        retIDs[cnt++] = temp->msgId;
    }
    return cnt;
}

// userId가 follow하고 있는 userTb 요소들을 모은다.
// 우선순위에 따라 정렬한다. -> 힙정렬 아니면 병합정렬로
int getMessages(int userID, int retIDs[])
{
    gHeap.init();

    int searchCnt = 0;
    for (Node* temp = gUserTb[userID].head.next; temp != &gUserTb[userID].tail; temp = temp->next, searchCnt++)
    {
        if (searchCnt >= 5) break;
        gHeap.heapPush(temp->msgId);
    }

    for (int i = 0; i < gFollowTb[userID][1000]; i++)
    {
        int userId = gFollowTb[userID][i];
        int searchCnt = 0;
        for (Node* temp = gUserTb[userId].head.next; temp != &gUserTb[userId].tail; temp = temp->next, searchCnt++)
        {
            if (searchCnt >= 5) break;
            gHeap.heapPush(temp->msgId);
        }
    }
    
    int cnt = 0;
    while ((0 != gHeap.heapSize) && (cnt < 5)) //탈출조건: heap이 비어있거나 cnt가 5이다.
    {
        int value;
        gHeap.heapPop(&value);
        retIDs[cnt++] = value;
    }
    return cnt;
}