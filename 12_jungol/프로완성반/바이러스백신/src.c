// http://jungol.co.kr/xpert/contestproblem.php?bo_table=prelearning&cid=1475&pid=9&al=005004&stx=9
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
//#include <assert.h>

#define MAX_PROGRAM_LEN (1000 + 1)
#define MAX_PROGRAM_CNT (100 + 1)
#define MAX_TABLE       (2 * MAX_PROGRAM_LEN)
#define KEY_CNT (3)

int gProgramCnt;
int gVirusLen;
int gProgramLen;
int gProgram[MAX_PROGRAM_CNT][MAX_PROGRAM_LEN];
int gDetectCnt[MAX_PROGRAM_LEN];

bool isSameKey(const int* key1, const int* key2);

typedef struct
{
    int key[KEY_CNT]; //index; 0: 바이러스 합, 1: 바이러스 끝 지점, 2: 프로그램 Id
}Hash;
Hash tb[MAX_TABLE];

unsigned long hash(const int key)
{
    // 바이러스 부분합으로 hashing을 한다.
    unsigned long hash = 5381;
    hash = (((hash << 5) + hash) + key) % MAX_TABLE;
    return hash % MAX_TABLE;
}

int find(const int* key)
{
    unsigned long h = hash(key[0]);
    int cnt = MAX_TABLE;

    while (tb[h].key[0] != 0 && cnt--)
    {
        if (isSameKey(tb[h].key, key))
        {
            return 1;
        }
        h = (h + 1) % MAX_TABLE;
    }
    return 0;
}

// hashing이 동일할 때, 같은 key인지를 확인하기 위해서는,
// 바이러스 끝 지점의 좌표와 프로그램id를 가지고, 바이러스 패턴을 비교한다.
bool isSameKey(const int* key1, const int* key2)
{
    bool bRet = true;

    if (key1[0] != key2[0])
    {
        bRet = false;
    }
    else
    {
        int programId = key2[1];
        int endPoint1 = key1[2];
        int endPoint2 = key2[2];
        
        for (int i = 0; i < 4; i++)
        {
            if (gProgram[0][endPoint1 - i] != gProgram[programId][endPoint2 - i])
            {
                bRet = false;
                break;
            }
            bRet = true;
        }

        if (false == bRet)
        {
            for (int i = 0; i < 4; i++)
            {
                if (gProgram[0][endPoint1 - i] != gProgram[programId][endPoint2 + i - gVirusLen + 1])
                {
                    bRet = false;
                    break;
                }
                bRet = true;
            }
        }
    }
    return bRet;
}

void copyArr(int* aDec, const int* aSrc)
{
    for (int i = 0; i < KEY_CNT; i++)
    {
        aDec[i] = aSrc[i];
    }
}

int add(const int* key)
{
    unsigned long h = hash(key[0]);

    while (tb[h].key[0] != 0)
    {
        if (isSameKey(tb[h].key, key))
        {
            return 0;
        }

        h = (h + 1) % MAX_TABLE;
    }
    copyArr(tb[h].key, key);
    return 1;
}

bool bNeedToCheckMore;

void setVirusSum(int programId)
{
    bNeedToCheckMore = false;
    scanf("%d", &gProgramLen);
    int sum[MAX_PROGRAM_LEN] = { 0, };

    for (int i = 1; i <= gProgramLen; i++)
    {
        scanf("%d", &gProgram[programId][i]);
        sum[i] = sum[i - 1] + gProgram[programId][i];

        int k = i - gVirusLen;
        if (k >= 0)
        {
            int virusSum = sum[i] - sum[k];
            int key[KEY_CNT] = { virusSum, programId, i};

            if (0 == programId)
            {
                add(key);
            }
            else
            {
                if (find(key))
                {
                    if (programId > gDetectCnt[i])
                    {
                        gDetectCnt[i]++;
                        if (programId >= gDetectCnt[i])
                        {
                            bNeedToCheckMore = true;
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &gProgramCnt, &gVirusLen);

    // 0번 program의 바이러스 패턴으로 hashTb를 만든다.
    setVirusSum(0);

    // 1번 ~ N번 program에, 0번 program내의 바이러스 패턴과 동일한 것이 있는지 찾는다.
    for (int i = 1; i < gProgramCnt; i++)
    {
        setVirusSum(i);

        //i번 program에, 0번 program내의 바이러스 패턴과 동일한 것이 없다면, 더 이상 찾을 필요가 없다.
        if (false == bNeedToCheckMore)
        {
            printf("NO");
            return 0;
        }
    }
    printf("YES");
    return 0;
}