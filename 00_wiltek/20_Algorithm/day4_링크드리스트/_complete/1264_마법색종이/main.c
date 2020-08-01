#include <stdio.h>

#define DEBUG 1
#define LEN ((int)4e4)
#define MAXN ((int)3e4 + 10)

int W, H;               //가로, 세로
int N;                  //점 개수
typedef struct tree 
{                       //full binary tree
    int sh, sw; 
    int eh, ew; 
    int color;
    struct tree *left;
    struct tree *right;
}TREE;

TREE *root;
int ptr;
TREE node[MAXN * 2];//두 장으로 나뉘므로 점 두배면 충분

TREE *myalloc(int sh, int sw, int eh, int ew, int color) 
{
    TREE *p = &node[ptr++];
    p->sh = sh; 
    p->sw = sw; 
    p->eh = eh; 
    p->ew = ew; 
    p->color = color;
    p->left = p->right = NULL;
    return p;
}

int check(TREE *p, int h, int w) 
{
    return (p->sh <= h) && (h <= p->eh) && (p->sw <= w) && (w <= p->ew);
}

void insert(TREE *p, int h, int w) 
{
    if (p->left == NULL) //종단 노드임; full binary tree이므로 하나의 자식만 확인해도 충분
    {
        if (p->color == 0) 
        {//흰색은 수평선으로 자르기
            p->left  = myalloc(p->sh, p->sw, h, p->ew, 1);
            p->right = myalloc(h, p->sw, p->eh, p->ew, 1);
        }
        else 
        {//검은색은 수직선으로 자르기
            p->left  = myalloc(p->sh, p->sw, p->eh, w, 0);
            p->right = myalloc(p->sh, w, p->eh, p->ew, 0);
        }
        return;
    }
    if (check(p->left, h, w)) 
        insert(p->left, h, w);
    
    else 
        insert(p->right, h, w);
}

int maxarea, minarea;

void search(TREE *p) 
{
    if (p->left == NULL) //종단 노드임
    {
        int area = (p->eh - p->sh) * (p->ew - p->sw);
        if (maxarea < area) maxarea = area;
        if (minarea > area) minarea = area;
        return;
    }
    search(p->left); 
    search(p->right);
}

void InputData() 
{
    scanf("%d %d", &W, &H);
    scanf("%d", &N);
}

void init()
{
    maxarea = 0; 
    minarea = LEN * LEN;
    ptr = 0; 
    root = myalloc(0, 0, H, W, 0);
}

void solve() {
    int w, h;

    init();

    //색종이 자르기
    for (int i = 0; i < N; i++) 
    {
        scanf("%d %d", &w, &h);
        insert(root, h, w);
    }

    //색종이 탐색
    search(root);
    printf("%d %d\n", maxarea, minarea);
}

int main() 
{
#ifdef DEBUG
    freopen("input.txt", "r", stdin);
#endif
    InputData();
    solve();
    return 0;
}