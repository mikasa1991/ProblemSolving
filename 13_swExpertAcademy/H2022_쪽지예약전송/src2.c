#define MAXM 3

typedef struct {
    int timestamp;
    int uID;
    int mID_next;
    bool read_done;
    bool delete_done;
}msgbox_t;

msgbox_t Sentbox[100001];
msgbox_t Inbox[100001];

int userN;
int userSentboxHead[1001];
int userInboxHead[1001];

void init(int N)
{
    for (int i = 1; i <= N; i++) userSentboxHead[i] = userInboxHead[i] = 0;
    userN = N;
}

void sendMessage(int cTimestamp, int uID1, int uID2, int mID, int scheduleTimestamp)
{
    //sentbox
    Sentbox[mID] = { cTimestamp, uID1, userSentboxHead[uID1], 0, 0 };
    userSentboxHead[uID1] = mID;

    //inbox
    Inbox[mID] = { scheduleTimestamp, uID2, userInboxHead[uID2], 0, 0 };
    userInboxHead[uID2] = mID;
}

int retrieveSentbox(int cTimestamp, int uID, int mIDList[], int uIDList[], int readList[])
{
    int cnt = 0;
    int mID = userSentboxHead[uID];
    while (mID != 0) {
        if (Sentbox[mID].delete_done == 0) {
            mIDList[cnt] = mID;
            uIDList[cnt] = Inbox[mID].uID;
            readList[cnt] = Inbox[mID].read_done;
            cnt++;
            if (cnt == MAXM) break;
        }
        mID = Sentbox[mID].mID_next;
    }

    return cnt;
}

int retrieveInbox(int cTimestamp, int uID, int mIDList[], int uIDList[], int readList[])
{
    int mID0 = 0, mID1 = 0, mID2 = 0;
    int timestamp0 = 0, timestamp1 = 0, timestamp2 = 0;

    int timestamp;
    int cnt = 0;
    int mID = userInboxHead[uID];
    while (mID != 0) {
        timestamp = Inbox[mID].timestamp;
        if (Inbox[mID].delete_done == 0 && timestamp <= cTimestamp) {
            if (timestamp > timestamp2) {
                mID0 = mID1; mID1 = mID2; mID2 = mID;
                timestamp0 = timestamp1; timestamp1 = timestamp2; timestamp2 = timestamp;
            }
            else if (timestamp > timestamp1) {
                mID0 = mID1; mID1 = mID;
                timestamp0 = timestamp1; timestamp1 = timestamp;
            }
            else if (timestamp > timestamp0) {
                mID0 = mID;
                timestamp0 = timestamp;
            }
        }
        mID = Inbox[mID].mID_next;
    }

    if (mID2) {
        mIDList[0] = mID2;
        uIDList[0] = Sentbox[mID2].uID;
        readList[0] = Inbox[mID2].read_done;
        cnt++;
    }
    if (mID1) {
        mIDList[1] = mID1;
        uIDList[1] = Sentbox[mID1].uID;
        readList[1] = Inbox[mID1].read_done;
        cnt++;
    }
    if (mID0) {
        mIDList[2] = mID0;
        uIDList[2] = Sentbox[mID0].uID;
        readList[2] = Inbox[mID0].read_done;
        cnt++;
    }

    return cnt;
}

int readMessage(int cTimestamp, int uID, int mID)
{
    if (Sentbox[mID].uID == uID && Sentbox[mID].delete_done == 0) {
        Sentbox[mID].read_done = 1;
        return 1;
    }
    else if (Inbox[mID].uID == uID && Inbox[mID].timestamp <= cTimestamp && Inbox[mID].delete_done == 0) {
        Inbox[mID].read_done = 1;
        return 1;
    }

    return 0;
}

int deleteMessage(int cTimestamp, int uID, int mID)
{
    if (Sentbox[mID].uID == uID && Sentbox[mID].delete_done == 0) {
        Sentbox[mID].delete_done = 1;
        if (Inbox[mID].timestamp > cTimestamp) Inbox[mID].delete_done = 1;
        return 1;
    }
    else if (Inbox[mID].uID == uID && Inbox[mID].timestamp < cTimestamp && Inbox[mID].delete_done == 0) {
        Inbox[mID].delete_done = 1;
        return 1;
    }

    return 0;
}