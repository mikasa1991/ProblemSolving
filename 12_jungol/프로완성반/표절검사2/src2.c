//http://jungol.co.kr/xpert/contestproblem.php?bo_table=prelearning&cid=1475&pid=11&al=005004&stx=11
//표절검사2

/// ===== user.cpp  =====
#ifndef NULL
#define NULL 0
#endif 

const int SIZE = 1 << 21;
const int MOD = SIZE - 1;
int N;
int bcnt;
int org[10001][201];

struct Hash
{
    int id;
    int pos;
    Hash* next;
    
    Hash* myAlloc(int _id, int _pos, Hash* _next)
    {
        id = _id;
        pos = _pos;
        next = _next;
        return this;
    }
} buf[SIZE], *hash[SIZE];

int bit7(int a)
{
    return (a >> 8) & ((1 << 7) - 1);
}

int key_calc(int a, int b, int c)
{
    return (bit7(a) << 14) + (bit7(b) << 7) + bit7(c);
}

void initUser(int soundNum)
{
    bcnt = 0;
    N = soundNum;
    for (int i = 0; i < SIZE; i++)
    {
        hash[i] = 0;
    }
}

int limit[3][8] = {
    {-127, -127, -127, -127, 128, 128, 128, 128},
    {-127, -127, 128, 128, -127, -127, 128, 128},
    {-127, 128, -127, 128, -127, 128, -127, 128},
};

void registerSound(int soundID, int soundLen, int soundArr[200])
{
    for (int i = 0; i < soundLen; i++)
    {
        org[soundID][i] = soundArr[i];
    }

    for (int i = 0; i <= soundLen - 8; i++)
    {
        int key = key_calc(soundArr[i], soundArr[i + 1], soundArr[i + 2]);
        hash[key] = buf[bcnt++].myAlloc(soundID, i, hash[key]);
    }
}

int chk(int a[], int b[])
{
    int bRet = 1;
    for (int i = 0; i < 8; i++)
    {
        if (a[i] - 128 > b[i] || a[i] + 127 < b[i])
        {
            bRet = 0;
        }
    }
    return bRet;
}

int plagiarismCheck(int arr[8])
{
    for (int i = 0; i < 8; i++)
    {
        int key = key_calc(arr[0] + limit[0][i], 
            arr[1] + limit[1][i], arr[2] + limit[2][i]);

        for (Hash* p = hash[key]; p != 0; p = p->next)
        {
            if (chk(org[p->id] + p->pos, arr))
            {
                return p->id;
            }
        }
    }

    return 0;
}