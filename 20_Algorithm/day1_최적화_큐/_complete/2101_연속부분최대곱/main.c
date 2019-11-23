#include <stdio.h>
#include <assert.h>
#define MAXN ((int)1e4 + 10)


//O(N)
double solve()
{
    int N;
    double num;

    scanf("%d", &N);

    double max = 0;
    double buf = 1;

    for(int i = 0; i < N; i++)
    {
        scanf("%lf", &num);
        
        if(buf <= 1) buf = num;     //누적곱이 1이하면 다음을 곱해도 이전보다 커질 수가 없다
                                    //이 전에 최대값이 나왔어도 갱신을 계속 했으니까 문제없다
        else buf *= num;            //누적곱이 1초과면 곱해라 

        if(max < buf) max = buf;    //최대값 갱신 계속
    }
    return max;
}

int main()
{
    freopen("input.txt", "r", stdin);
    double ans;
    ans = solve();
    printf("%.3lf", ans);
    return 0;
}