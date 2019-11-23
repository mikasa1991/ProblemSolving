/*
http://jungol.co.kr/xpert/viewp.php?bo_table=&bo_table&id=3101&sca=50
*/

#include <stdio.h> 
#define MAXN 10000

int N, K;
int que[MAXN];                  //circular queue 
int front = 0;
int rear = -1;
int queue_size = 0;

void enqueue(int d)
{
    rear = (rear + 1) % MAXN;
    que[rear] = d;
    queue_size++;
}

int dequeue()
{
    int temp = que[front];
    front = (front + 1) % MAXN;
    queue_size--;
    return temp;
}

void InputData() 
{
    scanf("%d %d", &N, &K);
}

void init()
{
    front = 0;
    rear = -1;
}

void solve() 
{
    init(); 

    for (int i = 1; i <= N; i++) 
        enqueue(i);
    
    int temp = 0;

    for (int i = 1; i < N; i++)         //(사람 수 - 1)만큼 반복하는데,
    {
        for (int j = 1; j < K; j++)     //첫번째 front 사람 기준으로 K-1번째까지 반복 
        {
            temp = dequeue(); 
            enqueue(temp);
        }
        temp = dequeue();               //K번째 사람 
        printf("%d ", temp); 
    }
    temp = dequeue();                   //마지막 사람(마지막 사람은 K번째냐 따질 필요가 없으니까)
    printf("%d ", temp);
}

int main() {
#if 1
    freopen("input.txt", "r", stdin);
#endif
    InputData();
    solve();
    return 0;
}