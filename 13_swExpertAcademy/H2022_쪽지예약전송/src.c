#define MAXM	       3
#define NULL	       0
#define MAX_USER       ((int)1e4 + 10)
#define MAX_MSG		   ((int)1e5 + 10)
#define MAX_NODE	   (2 * MAX_MSG)

int gArr[MAX_MSG];
int gBuf[MAX_MSG];
bool compare(int a, int b, int para);

bool isSendDone(int a, int b)
{
	return (a >= b);
}

void mergeSort(int s, int e, int para)
{
	int m = (s + e) / 2;

	//divide
	if (s < e)
	{
		mergeSort(s, m, para);
		mergeSort(m + 1, e, para);
	}

	//merge
	int i = s;
	int j = m + 1;
	int k = s;

	// 탈출조건: 둘 중 하나라도 
	while (i <= m && j <= e)
	{
		if (compare(gArr[i], gArr[j], para)) gBuf[k++] = gArr[i++];
		else gBuf[k++] = gArr[j++];
	}

	while (i <= m) gBuf[k++] = gArr[i++];
	while (j <= e) gBuf[k++] = gArr[j++];

	for (int i = s; i <= e; i++)
	{
		gArr[i] = gBuf[i];
	}
}

struct Node
{
	Node* prev;
	Node* next;
	bool bReadDone;
	int msgId;
	void init()
	{
		prev = NULL;
		next = NULL;
		bReadDone = false;
		msgId = 0;
	}

	Node* alloc()
	{
		return this;
	}

	Node* del()
	{
		next->prev = prev;
		prev->next = next;
		return this;
	}
};
Node gFreeNode[MAX_NODE];
int gUsedNodeCnt;

struct List
{
	Node head;
	Node tail;
	int nodeCnt;

	void init()
	{
		head.init();
		tail.init();
		nodeCnt = 0;

		head.next = &tail;
		tail.prev = &head;
	}

	Node* addNode(int mId)
	{
		Node* pNode = gFreeNode[gUsedNodeCnt++].alloc();
		pNode->init();
		pNode->msgId = mId;

		pNode->next = head.next;
		pNode->prev = &head;
		head.next->prev = pNode;
		head.next = pNode;

		nodeCnt++;
		return pNode;
	}
};

struct MsgBox
{
	List sendBoxList;
	List inBoxList;

	void init()
	{
		sendBoxList.init();
		inBoxList.init();
	}
};
MsgBox gMsgBox[MAX_USER];

struct Msg
{
	int senderId;
	int receiverId;
	int time;
	int scheduleTime;
	Node* pSenderNode;
	Node* pReceiverNode;
	bool bExistSendBox;
	bool bExistInBox;

	void init()
	{
		senderId = 0;
		receiverId = 0;
		time = 0;
		scheduleTime = 0;
		pSenderNode = NULL;
		pReceiverNode = NULL;
		bExistSendBox = true;
		bExistInBox = true;
	}

	void setter(int uId1, int uId2, Node* pSendNode, Node* pReciNode, int t, int st)
	{
		senderId = uId1;
		receiverId = uId2;
		pSenderNode = pSendNode;
		pReceiverNode = pReciNode;
		time = t;
		scheduleTime = st;
	}

	void deleteMsgSendBox(int msgId)
	{
		pSenderNode->del();
		//pSenderNode = NULL;
		//senderId = INVALID_MSG_ID;
		bExistSendBox = false;
		gMsgBox[senderId].sendBoxList.nodeCnt--;
	}

	void deleteMsgInBox(int msgId)
	{
		pReceiverNode->del();
		//pReceiverNode = NULL;
		//receiverId = INVALID_MSG_ID;
		bExistInBox = false;
		gMsgBox[receiverId].inBoxList.nodeCnt--;
	}
};
Msg gMsgTb[MAX_MSG];

bool compare(int a, int b, int para)
{
	bool bRet;
	if (0 == para) // sendBox
	{
		bRet = (gMsgTb[a].time > gMsgTb[b].time);
	}
	else // InBox
	{
		if (gMsgTb[a].scheduleTime == gMsgTb[b].scheduleTime)
		{
			bRet = (a > b);
		}
		else
		{
			bRet = (gMsgTb[a].scheduleTime > gMsgTb[b].scheduleTime);
		}
	}
	return bRet;
}

void init(int N)
{
	gUsedNodeCnt = 0;
	for (int i = 0; i < MAX_USER; i++)
	{
		gMsgBox[i].init();
	}
	{
	for (int i = 0; i < MAX_MSG; i++)
		gMsgTb[i].init();
	}
}

void sendMessage(int cTimestamp, int uID1, int uID2, int mID, int scheduleTimestamp)
{
	Node* pSenderNode = gMsgBox[uID1].sendBoxList.addNode(mID);
	Node* pReceiverNode = gMsgBox[uID2].inBoxList.addNode(mID);

	gMsgTb[mID].setter(uID1, uID2, pSenderNode, pReceiverNode, cTimestamp, scheduleTimestamp);
}

int retrieveSentbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM])
{
	int cnt = 0;
	List* pList = &gMsgBox[uID].sendBoxList;
	for (Node* temp = pList->head.next; temp != &pList->tail; temp = temp->next)
	{
		gArr[cnt++] = temp->msgId;
	}
	mergeSort(0, cnt - 1, 0/*sendbox*/);

	int loopCnt = 0;
	if (cnt < MAXM) loopCnt = cnt;
	else			loopCnt = MAXM;

	for (int i = 0; (i < loopCnt); i++)
	{
		int msgId = gArr[i];
		mIDList[i] = msgId;
		uIDList[i] = gMsgTb[msgId].receiverId;
		readList[i] = gMsgTb[msgId].pReceiverNode->bReadDone;
	}
	return loopCnt;
}

int retrieveInbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM])
{
	int cnt = 0;
	List* pList = &gMsgBox[uID].inBoxList;
	for (Node* temp = pList->head.next; temp != &pList->tail; temp = temp->next)
	{
		int mId = temp->msgId;
		if (true == isSendDone(cTimestamp, gMsgTb[mId].scheduleTime))
		{
			gArr[cnt++] =mId;
		}
	}
	mergeSort(0, cnt - 1, 1/*inbox*/);

	int loopCnt = 0;
	if (cnt < MAXM) loopCnt = cnt;
	else			loopCnt = MAXM;

	for (int i = 0; (i < loopCnt); i++)
	{
		int msgId = gArr[i];
		mIDList[i] = msgId;
		uIDList[i] = gMsgTb[msgId].senderId;
		readList[i] = gMsgTb[msgId].pReceiverNode->bReadDone;
	}
	return loopCnt;
}

int readMessage(int cTimestamp, int uID, int mID)
{
	bool bIsSuccess = false;
	if (uID == gMsgTb[mID].senderId && true == gMsgTb[mID].bExistSendBox)
	{
		gMsgTb[mID].pSenderNode->bReadDone = true;
		bIsSuccess = true;
	}

	if (uID == gMsgTb[mID].receiverId && true == gMsgTb[mID].bExistInBox)
	{
		if (true == isSendDone(cTimestamp, gMsgTb[mID].scheduleTime))
		{
			gMsgTb[mID].pReceiverNode->bReadDone = true;
			bIsSuccess = true;
		}
	}
	return bIsSuccess;
}

int deleteMessage(int cTimestamp, int uID, int mID)
{
	bool bIsSuccess = false;
	if (uID == gMsgTb[mID].senderId && true == gMsgTb[mID].bExistSendBox)
	{
		if (false == isSendDone(cTimestamp, gMsgTb[mID].scheduleTime))
		{
			gMsgTb[mID].deleteMsgInBox(mID);
		}
		gMsgTb[mID].deleteMsgSendBox(mID);
		bIsSuccess = true;
	}

	if (uID == gMsgTb[mID].receiverId && true == gMsgTb[mID].bExistInBox)
	{
		if (true == isSendDone(cTimestamp, gMsgTb[mID].scheduleTime))
		{
			gMsgTb[mID].deleteMsgInBox(mID);
			bIsSuccess = true;
		}
	}
	return bIsSuccess;
}