#include <stdio.h>

#define DEBUG 1
#define INFLIMIT ((int)1e6)
#define INF (1ll << 60)
#define MAXN ((int)1e5 + 10)
#define MAXM ((int)2e5 + 10)
typedef long long S64;
int N;//도시 수
int M;//도로 수
int K;//점렴당한 도시 수
int S;//위험한 도시 범위
int p;//안전도시 숙박비
int q;//위험한도시 숙박비
int A[MAXN];//점령당한 도시 번호
 
typedef struct node {
    int e;
    struct node *next;
}NODE;
 
NODE link[MAXN];//인덱스가 출발도시, 내용에 도착도시
int ptr;
NODE dnode[MAXM * 2 + 10];

NODE *myalloc(int e) 
{
    NODE *pt = &dnode[ptr++];
    pt->e = e; 
    pt->next = NULL;
    return pt;
}

void insert_next_to(NODE *pt, int e)
{
    NODE *new_node = myalloc(e);

    new_node->next = pt->next;
    pt->next = new_node;
}

int limit[MAXN];//index도시에서부터 가장 가까운 점령도시까지의 거리
S64 visit[MAXN];//출발 도시에서 각 도시까지 드는 최소 비용(중복방문 여부 판단용)
 
typedef struct {
    int n;
    S64 cost;
}HEAP;
HEAP heap[MAXM];//minimum heap
int lastn;
 
void swap(HEAP *a, HEAP *b)
{
    HEAP temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
 
void push(int n, S64 cost) 
{
    heap[++lastn].n = n; 
    heap[lastn].cost = cost;
    register int C = lastn, P = C / 2;
    while (P && (heap[P].cost > heap[C].cost)) 
    {
        swap(&heap[P], &heap[C]);
        C = P; 
        P = C / 2;
    }
}
 
HEAP pop(void) {
    HEAP ret = heap[1]; 
    heap[1] = heap[lastn--];
    register int P = 1, L = 2, R = 3, C;
    while (L <= lastn) 
    {
        if (R > lastn) C = L;
        else C = (heap[L].cost <= heap[R].cost) ? L : R;
        if (heap[P].cost <= heap[C].cost) break;
        swap(&heap[P], &heap[C]);
        P = C; 
        L = P * 2; 
        R = L + 1;
    }
    return ret;
}
int empty() { return lastn == 0; }
 
void init() {
    ptr = 0;
    for (int i = 1; i <= N; i++) {
        link[i].next = NULL;
    }
}
 
void print_link()
{
    for(int i = 1; i <= N; i++)
    {
        NODE *temp = link[i].next;
        printf("link[%d]: ", i);
        
        while(temp != NULL)
        {
            printf("%d ", temp->e);
            temp = temp->next;
        }
        
        puts("");
    }
}

void InputData() 
{
    int i; 
    int s, e;
    scanf("%d %d %d %d", &N, &M, &K, &S);
    scanf("%d %d", &p, &q);
    for (i = 0; i < K; i++) {
        scanf("%d", &A[i]);
    }
    init(N);
    for (i = 0; i < M; i++) {
        scanf("%d %d", &s, &e);
        insert_next_to(&link[s], e);
        insert_next_to(&link[e], s);    //양방향이므로 e->s도 저장해야 함            
    }
}

/*
*/
void limit_BFS()                        //사실 일반FIFO Queue를 사용하면 되지만 이미 만든 우선순위큐 사용함
{
    //1.초기화
    for (int i = 1; i <= N; i++) 
    {
        limit[i] = INFLIMIT;
    }
    lastn = 0;//큐 초기화
 
    //2.시작위치 큐에 저장
    for (int i = 0; i < K; i++) {//좀비에게 점령당한 도시가 모두 출발지임
        push(A[i], 0); 
        limit[A[i]] = 0;
    }
 
    //3.반복문
    while (!empty()) 
    {
        int cur = pop().n;
        for (NODE *pt = link[cur].next; pt != NULL; pt = pt->next) 
        {
            int e = pt->e;
            if (limit[e] <= limit[cur] + 1) continue;
            limit[e] = limit[cur] + 1;
            push(e, limit[e]);
        }
    }
}
 
S64 BFS() {
    //1.초기화
    for (int i = 1; i <= N; i++) 
    {
        visit[i] = INF;
    }
    lastn = 0;//큐 초기화

    //2.시작위치 큐에 저장
    push(1, 0);             //도시번호, 비용
    visit[1] = 0;
    
    //3.반복문
    while (!empty()) 
    {
        HEAP tmp = pop(); 
        int cur = tmp.n;
 
        if (cur == N) 
        {   //꺼낸 도시가 도착지면 성공(단, 도착지는 비용을 지불하지 않으므로 빼야함)
            if (limit[N] <= S) tmp.cost -= q;   //위험한 도시인 경우
            else tmp.cost -= p;                 //안전한 도시인 경우
            return tmp.cost;
        }
 
        if (visit[cur] < tmp.cost) continue;                //중복임(가지치기)
 
        for (NODE *pt = link[cur].next; pt; pt = pt->next)  //인접한 다음 도시를 확인해야하는데, 
        {
            int e = pt->e;                          //e = 다음 도시 번호 
            S64 e_cost;
            if (limit[e] == 0) continue;            //방문 불가(좀비가 점령한 도시임)
            
            //비용 계산
            if (limit[e] <= S)                      //위험한 도시
                e_cost = tmp.cost + q; 
            else //limit[e] > S                     //안전한 도시
                e_cost = tmp.cost + p;
            
            if (visit[e] <= e_cost) continue;         //이전보다 좋지않음
            push(e, e_cost); 
            visit[e] = e_cost;
        }
    }
    return -1;                                      //이런 경우 없음
}

S64 solve(void) 
{
    limit_BFS();//좀비에게 점령당한 도시와의 거리 구하기
    return BFS();//최소비용찾기
}
int main(void) {
#ifdef DEBUG
    freopen("input.txt", "r", stdin);
#endif
    InputData();
    print_link();
    S64 ans = solve();
    printf("%lld\n", ans);
    return 0;
}