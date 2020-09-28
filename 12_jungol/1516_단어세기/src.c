//http://jungol.co.kr/bbs/board.php?bo_table=pbank&wr_id=788&sca=20
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>
#include <string.h>

static const int MAX_STRING = 200 + 1;
char ganStr[MAX_STRING][MAX_STRING];
char ganTemp[MAX_STRING][MAX_STRING];
void MergeSort(int s, int e)
{
    if (s >= e) return;

    int m = (s + e) / 2;
    MergeSort(s    , m);
    MergeSort(m + 1, e);

    int i = s;
    int j = m + 1;
    int k = s;

    while ((i <= m) && (j <= e))
    {
        if (0 > strcmp(ganStr[i], ganStr[j]))
        {
            strcpy(ganTemp[k++], ganStr[i++]);
        }
        else
        {
            strcpy(ganTemp[k++], ganStr[j++]);
        }
    }
    while (i <= m) strcpy(ganTemp[k++], ganStr[i++]);
    while (j <= e) strcpy(ganTemp[k++], ganStr[j++]);

    for (int k = s; k <= e; k++)
    {
        strcpy(ganStr[k], ganTemp[k]);
    }
}

void PrintFrequency(int n)
{
    int cnt = 1;
    for (int i = 0; i < n; i++)
    {
        if (0 == strcmp(ganStr[i], ganStr[i + 1]))
        {
            cnt++;
        }
        else
        {
            printf("%s : %d\n", ganStr[i], cnt);
            cnt = 1;
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    for (;;)
    {
        char anTemp[MAX_STRING];
        fgets(anTemp, MAX_STRING, stdin);
        if (0 == strcmp(anTemp, "END")) break;

        anTemp[strlen(anTemp) - 1] = 0;
        //printf("%s\n", anTemp);

        char* ptr = strtok(anTemp, " ");
        int i = 0;
        while (ptr != NULL)
        {
            //printf("%s\n", ptr);
            strcpy(ganStr[i++], ptr);
            ptr = strtok(NULL, " ");
        }
        MergeSort(0, i-1);
        PrintFrequency(i);
    }
    return 0;
}