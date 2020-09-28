//http://jungol.co.kr/bbs/board.php?bo_table=pbank&wr_id=2375&sca=99&sfl=wr_subject&stx=%EC%A7%84%EB%B2%95
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>
#include <string.h>

const int MAX_STRING = 100;
int main()
{
    freopen("input.txt", "r", stdin);
    int A, B;
    char N[MAX_STRING];
    while (1)
    {
        scanf("%d %s %d", &A, &N, &B);
        if (A == 0) break;
        if (N[0] == '0')
        {
            printf("0\n");
            continue;
        }

        long long i;
        long long j = 1;
        long long sum = 0;
        for (i = strlen(N) - 1; i >= 0; i--) 
        {
            if (N[i] >= 'A')
            {
                N[i] = '9' + (N[i] - 'A') + 1;
            }
            sum += j * (N[i] - '0');
            j *= A;
        }

        char str[MAX_STRING];
        i = 0;
        for (; sum > 0; sum = sum / B)
        {
            if ((sum % B) > 9) str[i++] = (sum % B) - 10 + 'A';
            else               str[i++] = (sum % B) + '0';
        }

        for (i = i - 1; i >= 0; i--)
        {
            printf("%c", str[i]);
        }
        printf("\n");
    }
}