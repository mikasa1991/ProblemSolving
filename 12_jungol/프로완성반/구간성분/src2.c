/**************************************************************
    Problem: 2918
    User: dong_hee.lee
    Language: C++
    Result: Success
    Time:422 ms
    Memory:1272 kb
****************************************************************/

#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>

#define MOD (10000)

int getStrLen(const char* str)
{
    int cnt = 0;
    while (*str++)
    {
        cnt++;
    }
    return cnt;
}

#define STR_LEN (1500 + 10)

int alen;
int blen;
int sum1[STR_LEN];
int sum2[STR_LEN];
char A[STR_LEN];
char B[STR_LEN];

struct data
{
    int pos;
    data* next;
    data* myAlloc(int _pos, data* _next)
    {
        pos = _pos;
        next = _next;
        return this;
    }
};
data buf[STR_LEN];
data* hash[MOD];

int chkval(int ap, int bp, int n)
{
    int i;
    int cnt[26] = { 0, };
    for (i = ap - n + 1; i <= ap; i++)
    {
        cnt[A[i] - 'a']++;
    }
    for (i = bp - n + 1; i <= bp; i++)
    {
        cnt[B[i] - 'a']--;
        if (cnt[B[i] - 'a'] < 0)
        {
            return 0;
        }
    }
    return 1;
}

int check(int n)
{
    int i;
    int key;
    int bCnt = 0;

    for (i = 0; i < MOD; i++)
    {
        hash[i] = 0;
    }
    
    for (i = n; i <= alen; i++)
    {
        key = (sum1[i] - sum1[i - n]) % MOD;
        hash[key] = buf[bCnt++].myAlloc(i, hash[key]);
    }

    for (i = n; i <= blen; i++)
    {
        key = (sum2[i] - sum2[i - n]) % MOD;
        for (data* p = hash[key]; p; p = p->next)
        {
            if (chkval(p->pos, i, n))
            {
                return 1;
            }
        }
    }
    return 0;
}

int main()
{
    freopen("input.txt", "r", stdin);
    int i;
    scanf("%s %s", A + 1, B + 1);
    alen = getStrLen(A + 1);
    blen = getStrLen(B + 1);

#define pow(A) (A*A)
    for (i = 1; i <= alen; i++)
    {
        sum1[i] = sum1[i - 1] + pow((A[i] - ('a' - 1)));
    }

    for (i = 1; i <= blen; i++)
    {
        sum2[i] = sum2[i - 1] + pow((B[i] - ('a' - 1)));
    }
#define MIN(a,b) ((a < b) ? a : b)
    for (i = MIN(alen, blen); i > 0; i--)
    {
        if (check(i))
        {
            break;
        }
    }
    printf("%d", i);
    return 0;
}