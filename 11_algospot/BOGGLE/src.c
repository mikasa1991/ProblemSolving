//https://www.algospot.com/judge/problem/read/BOGGLE

#include <stdio.h>
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)
//#define DEBUG

#ifdef DEBUG
#define dprintf printf
#else
#define dprintf
#endif  //(DEBUG)

#define MAP_SIZE 5
#define MAX_WORD_COUNT (10+1)
#define MAX_WORD_SIZE (10+1)
#define DIR_CNT 8
char gMap[MAP_SIZE][MAP_SIZE];
char gWord[MAX_WORD_COUNT][MAX_WORD_SIZE];

int dr[DIR_CNT] = { 0, 1,  0, -1, 1,  1, -1, -1 };
int dc[DIR_CNT] = { 1, 0, -1,  0, 1, -1,  1, -1 };

bool IsNotInMap(int r, int c)
{
    return (r < 0) && (r >= MAP_SIZE) && (c < 0) && (c >= MAP_SIZE);
}

bool recursiveFunc(int r, int c, char* text, int i)
{
    dprintf("recursiveFunc(): (%d, %d) %s(text[%d]:%c)\n", r, c, text, i, text[i]);
    i++;
    if (text[i] == 0)   //NULL문자
    {
        return true;
    }
    for (int dir = 0; dir < DIR_CNT; dir++)
    {
        int nextR = r + dr[dir];
        int nextC = c + dc[dir];
        if (IsNotInMap(nextR, nextC)) continue;
        if (text[i] == gMap[nextR][nextC]) //i번째 문자가 일치하는가?
        {
            if (recursiveFunc(nextR, nextC, text, i))
            {
                return true;
            }
        }
    }
    return false;
}

void InitMap()
{
    for (int r = 0; r < MAP_SIZE; r++)
    {
        scanf("%s", &gMap[r]);
    }
}

void PrintMap()
{
    dprintf("---map---\n");
    for (int r = 0; r < MAP_SIZE; r++)
    {
        for (int c = 0; c < MAP_SIZE; c++)
        {
            dprintf("%c", gMap[r][c]);
        }
        dprintf("\n");
    }
}

int main()
{
    freopen("input.txt", "r", stdin);

    int nTcCnt;
    scanf("%d", &nTcCnt);
    for (int i = 0; i < nTcCnt; i++)
    {
        InitMap();
        PrintMap();
        int nWordCnt;
        scanf("%d", &nWordCnt);
        for (int i = 0; i < nWordCnt; i++) //각각의 Text에 대해서
        {
            scanf("%s", &gWord[i]);
            dprintf("\n%s ", gWord[i]);

            bool bFound = false;
            for (int r = 0; r < MAP_SIZE; r++)
            {
                for (int c = 0; c < MAP_SIZE; c++)
                {
                    if (gMap[r][c] == gWord[i][0]) //Text의 첫번째 문자가 Map에 있는가?
                    {
                        dprintf("\nfirst character founded!, r=%d, c=%d\n", r, c);
                        if (recursiveFunc(r, c, gWord[i], 0))
                        {
                            bFound = true;
                            printf("YES\n");
                            break;
                        }
                    }
                }
                if (bFound) break;
            }
            if (bFound)
                continue;   //goto nextWord
            else
                printf("NO\n");
        }
    }
    return 0;
}