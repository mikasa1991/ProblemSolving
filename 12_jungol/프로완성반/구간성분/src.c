/**************************************************************
    Problem: 2918
    User: dong_hee.lee
    Language: C++
    Result: Success
    Time:624 ms
    Memory:1292 kb
****************************************************************/
 
 
// 구간 성분
// http://jungol.co.kr/xpert/contestproblem.php?bo_table=prelearning&cid=1475&pid=10&al=005004&stx=10
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)
 
#include <stdio.h>
//#include <assert.h>
 
//#include <string.h>
#define MAX_LEN   (1500 + 10)
#define MAX_TABLE (10000)
#define ALPHABET_CNT (26)
#define KEY_CNT (3)
 
char A[MAX_LEN];
char B[MAX_LEN];
int sumOfMax[MAX_LEN];
int sumOfMin[MAX_LEN];
int getStrLen(const char* str);
char* pMinStr;
char* pMaxStr;
 
struct Hash
{
    int key[KEY_CNT];
    void init()
    {
        key[0] = 0;
        key[1] = 0;
        key[2] = -1;
    }
};
Hash tb[MAX_TABLE];
 
void copyKey(int* dest, const int* src)
{
    for (int i = 0; i < KEY_CNT; i++)
    {
        dest[i] = src[i];
    }
}
 
unsigned long hash(const int* key)
{
    unsigned long hash = 5381;
    int sum = 0;
    if (0 == key[2])
    {
        sum = sumOfMax[key[1]] - sumOfMax[key[0]];
    }
    else
    {
        sum = sumOfMin[key[1]] - sumOfMin[key[0]];
    }
 
    hash = (((hash << 5) + hash) + sum) % MAX_TABLE;
    return hash % MAX_TABLE;
}
 
bool isSameKey(const int* key1, const int* key2)
{
    bool bRet = true;
    int a[ALPHABET_CNT] = { 0, };
    int b[ALPHABET_CNT] = { 0, };
 
    int maxStId = 0;
    int minStId = 0;
 
    if (0 == key1[2])
    {
        maxStId = key1[0];
        minStId = key2[0];
    }
    else
    {
        maxStId = key2[0];
        minStId = key1[0];
    }
 
    int strlen = key1[1] - key1[0];
    for (int i = 0; i < strlen; i++)
    {
        a[pMinStr[minStId + i] - 'a']++;
        b[pMaxStr[maxStId + i] - 'a']++;
    }
 
    for (int i = 0; i < ALPHABET_CNT; i++)
    {
        // 양수 0
        if (a[i] != b[i])
        {
            bRet = false;
            break;
        }
    }
    return bRet;
}
 
int find(const int* key)
{
    unsigned long h = hash(key);
    int cnt = MAX_TABLE;
    int i = 1;
    while (tb[h].key[2] != -1 && cnt--)
    {
        if (isSameKey(tb[h].key, key))
        {
            return 1;
        }
        h = (h + (i*i)) % MAX_TABLE;
        i++;
    }
    return 0;
}
 
int add(const int* key)
{
    unsigned long h = hash(key);
    int i = 1;
    while (tb[h].key[2] != -1)
    {
        if (isSameKey(tb[h].key, key))
        {
            return 0;
        }
 
        h = (h + (i*i)) % MAX_TABLE;
        i++;
    }
    copyKey(tb[h].key, key);
    return 1;
}
 
void init()
{
    for (int i = 0; i < MAX_TABLE; i++)
    {
        tb[i].init();
    }
}
 
int getStrLen(const char* str)
{
    int cnt = 0;
    while (*str++)
    {
        cnt++;
    }
    return cnt;
}
 
int main()
{
    //freopen("input.txt", "r", stdin);
    scanf("%s %s", A, B);
 
    if (getStrLen(A) < getStrLen(B))
    {
        pMinStr = A;
        pMaxStr = B;
    }
    else
    {
        pMinStr = B;
        pMaxStr = A;
    }
 
    int strLenOfMin = getStrLen(pMinStr);
    int strLenOfMax = getStrLen(pMaxStr);
 
    for (int i = 1; i <= strLenOfMax; i++)
    {
        sumOfMax[i] = sumOfMax[i - 1] + (pMaxStr[i - 1])*(pMaxStr[i - 1]);
    }
 
    for (int i = 1; i <= strLenOfMin; i++)
    {
        sumOfMin[i] = sumOfMin[i - 1] + (pMinStr[i - 1])*(pMinStr[i - 1]);
    }
 
    for (int i = strLenOfMin; i > 0; i--)
    {
        // hashTb 초기화하기; key는 string
        init();
 
        // MaxString에서 i 길이에 해당하는 문자열 hash에 등록하기
        for (int j = 0; j < strLenOfMax; j++)
        {
            int endId = i + j;
            if (strLenOfMax < endId)
            {
                break;
            }
            int key[KEY_CNT] = { j, endId, 0};
            add(key);
        }
 
        // MinString에서 i 길이에 해당하는 문자열이 hashTb에 있는지 찾기
        for (int j = 0; j < strLenOfMin; j++)
        {
            int endId = i + j;
            if (strLenOfMin < (i + j))
            {
                break;
            }
 
            int key[KEY_CNT] = { j, endId, 1};
            if (find(key))
            {
                printf("%d", i);
                return 0;
            }
        }
    }
    printf("0");
    return 0;
}