//======== user.cpp ========
#ifndef NULL
#define NULL 0
#endif

#define MAXFIELD ((int)1e5)
#define CLIENT ((int)1e4 + 10)
 
extern int add_lot();
extern void assign(int lot_num, int s, int size, int member_id);
extern void back(int lot_num, int s, int size);
extern void grow(int lot_num, int s, int size, int crop);
 
typedef struct node 
{
    int lotnum;
    int s;
    int size;
    struct node *next;
}NODE;

NODE *field;
int fieldfreesize;  //이용가능 구역 크기
int ptr;
NODE fnode[CLIENT + 120];

NODE *myalloc(int lotnum, int s, int size, NODE *next) 
{
    NODE *p = &fnode[ptr++];
    p->lotnum = lotnum; 
    p->s = s; 
    p->size = size; 
    p->next = next;
    
    return p;
}

NODE *client[CLIENT];
 
//각 테스트 게이스마다 초기화
void init_member()
{
    ptr = 0; 
    field = NULL; 
    fieldfreesize = 0;
}
 
NODE *clientassign(NODE *p, int member_id, int size) 
{
    if (p->size == size) 
    {//이 노드까지 유저에게 줌, 다음 노드가 자유구역임
        NODE *ret = p->next; 
        p->next = NULL;
        assign(p->lotnum, p->s, p->size, member_id);    //api함수 호출해서 대여
        return ret;
    }

    else if (p->size > size) 
    {//이 노드를 두개로 나눠야 함, 앞은 유저, 뒤는 자유구역
        NODE *ret = myalloc(p->lotnum, p->s + size, p->size - size, p->next);
        p->size = size; 
        p->next = NULL;                                 //현재 노드 정보 수정(size와 next)
        assign(p->lotnum, p->s, p->size, member_id);    //api함수 호출해서 대여
        return ret;
    }

    //현재 노드로 사이즈 부족하므로 현재 노드 모두 유저에게 대여
    assign(p->lotnum, p->s, p->size, member_id);            //api함수 호출해서 대여
    return clientassign(p->next, member_id, size - p->size);//대여한 만큼 size에서 감소
}

//member_id​에 size크기의 구역을 할당한다.
void assign_member(int member_id, int size)
{
    if (fieldfreesize < size) 
    {
        field = myalloc(add_lot(), 0, MAXFIELD, field);
        fieldfreesize += MAXFIELD;
    }
    client[member_id] = field;                      //관리하는 맨 앞부분부터 대여
    fieldfreesize -= size;                          //대여크기 감소
    field = clientassign(field, member_id, size);   //자유구역중 size만큼 자르기
}
 
void clientback(NODE *p) 
{
    back(p->lotnum, p->s, p->size);     //api함수 호출해서 반납
    fieldfreesize += p->size;           //반납받은 크기 합산
    if (p->next) clientback(p->next);   //다음 노드 처리
    else 
    {                                   //마지막 노드이므로 next가 field를 가르키게하기
        p->next = field;
    }
}

//member_id에 할당된​ 구역을 해제한다. 채워진 작물도 초기화 된다.
void back_member(int member_id)
{
    clientback(client[member_id]);
    field = client[member_id];      //뒤에 붙이면 탐색해야 하므로 앞으로 추가
    client[member_id] = NULL;       //반납했으므로 초기화
}
 
void clientgrow(NODE *p, int crop) 
{
    grow(p->lotnum, p->s, p->size, crop);   //api함수 호출해서 작물 심기
    if(p->next) clientgrow(p->next, crop);  //다음 노드 처리
}

//member_id​에게 할당된 구역에 crop작물 배치
void grow_member(int member_id, int crop)
{
    clientgrow(client[member_id], crop);
}