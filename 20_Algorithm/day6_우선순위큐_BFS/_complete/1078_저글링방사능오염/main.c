/*
http://jungol.co.kr/xpert/viewp.php?bo_table=sm_bank&id=1078&alcate=&mtitle=%EB%AC%B8%EC%A0%9C%EC%9D%80%ED%96%89&al=003&altitle=&alname=&altag=&page=1
*/

#include <stdio.h>
 
#define MAX (100 + 10)
 
typedef struct _Pos
{
    int x;
    int y;
}Pos;
Pos queue[MAX*MAX];
int front;
int rear;
int time;
int q_size;
 
int map[MAX][MAX];
int x_size;
int y_size;
 
int x_s;
int y_s;
 
int zerg_cnt;
int kill_cnt;
 
void enqueue(Pos posi)
{
    //printf("enqueue_(%d, %d)\n", posi.x, posi.y);
    rear = (rear + 1) % (MAX*MAX);
    queue[rear] = posi;
    q_size++;
}
 
Pos dequeue()
{
    Pos temp = queue[front];
    //printf("dequeue_(%d, %d)\n", temp.x, temp.y);
    front = (front + 1) % (MAX*MAX);
    q_size--;
    return temp;
}
 
int is_q_empty()
{
    return q_size == 0;
}
 
int is_q_full()
{
    return q_size == MAX * MAX;
}
 
void init()
{
    front = 0;
    rear = -1;
    time = 3;
    q_size = 0;
    kill_cnt = 0;
}
 
void input_data()
{
    scanf("%d %d", &x_size, &y_size);
    //printf("%d %d\n", x_size, y_size);    //
    getchar();
    for (int y = 1; y <= y_size; y++)
    {
        for (int x = 1; x <= x_size; x++)
        {
            map[y][x] = getchar() - '0';
            if (map[y][x] == 1) zerg_cnt++;
            //printf("%d ", map[y][x]); //
        }
        getchar();
        //puts(""); //
    }
    scanf("%d %d", &x_s, &y_s);
    //printf("%d %d\n", x_s, y_s);  //
}
 
/*
시작점 큐에 넣기, 방문 표시
팝 하기
팝 한것과 인접한 거 큐에 넣기, 방문 표시
*/
 
int dx[4] = { 1,  0, -1, 0 };
int dy[4] = { 0, -1,  0, 1 };
 
void print_map()
{
    for (int y = 1; y <= y_size; y++)
    {
        for (int x = 1; x <= x_size; x++)
        {
            printf("%d ", map[y][x]);
        }
        puts("");
    }
    puts("");
}
 
int is_there_zerg(Pos p)
{
    return (p.x > 0) && (p.x <= MAX)
        && (p.y > 0) && (p.y <= MAX)
        && (map[p.y][p.x] == 1);
}
 
int solve()
{
    Pos p_start;
    p_start.x = x_s;
    p_start.y = y_s;
 
    init();
    enqueue(p_start);
    kill_cnt++;
    map[y_s][x_s] = time;
 
    while (!is_q_empty())//is not empty
    {
        Pos p = dequeue();
        for (int i = 0; i < 4; i++)  //4방향
        {
            Pos p_next;
            p_next.x = p.x + dx[i];
            p_next.y = p.y + dy[i];
 
            //저글링이 있다면, 큐에 넣고 방문표시
            if (is_there_zerg(p_next))  //범위 안에 존재 && 저글링(1) 있는 경우
            {
                enqueue(p_next);
                kill_cnt++;
                map[p_next.y][p_next.x] = map[p.y][p.x] + 1;
                time = map[p_next.y][p_next.x];
            }
        }
    }
    return time;
}
 
int main()
{
    int ans = 0;
#if 1
    freopen("input.txt", "r", stdin);
#endif
    input_data();
    //print_map();
    ans = solve();
    //print_map();
    printf("%d\n", ans);
    printf("%d\n", zerg_cnt - kill_cnt);
    return 0;
}
/**************************************************************
    Problem: 1814
    User: AXQ7106
    Language: C
    Result: Accepted
    Time:1 ms
    Memory:1304 kb
****************************************************************/