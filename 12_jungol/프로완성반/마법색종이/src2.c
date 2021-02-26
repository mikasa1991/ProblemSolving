// http://jungol.co.kr/xpert/contestproblem.php?bo_table=prelearning&cid=1475&pid=3&al=005004&stx=3
// No. C : 마법색종이
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)
 
#include <stdio.h>
#include <assert.h>
 
int H, W, N;
int maxAns = 0;
int minAns = 2e9;
int bn;
 
struct block
{
    int sx, sy, ex, ey, color;
    block* left;
    block* right;
 
    block* alloc(int _sx, int _sy, int _ex, int _ey, int _color)
    {
        sx = _sx;
        sy = _sy;
        ex = _ex;
        ey = _ey;
        color = _color;
        left = right = 0;
        return this;
    }
 
    void push(int x, int y, block buf[])
    {
        if (left == NULL)
        {
            if (color == 1)
            {
                left = buf[bn++].alloc(sx, sy, x, ey, 0);
                right = buf[bn++].alloc(x, sy, ex, ey, 0);
            }
            else
            {
                left = buf[bn++].alloc(sx, sy, ex, y, 1);
                right = buf[bn++].alloc(sx, y, ex, ey, 1);
            }
            return;
        }
        if (x < left->ex && y < left->ey) 
            left->push(x, y, buf);
        else
            right->push(x, y, buf);
    }
 
    void area()
    {
        if (left == NULL)
        {
            int area = (ex - sx) * (ey - sy);
            if (maxAns < area) maxAns = area;
            if (minAns > area) minAns = area;
            return;
        }
        left->area();
        right->area();
    }
};
 
block buf[60010];
block* root;
 
int main()
{
    //freopen("input.txt", "r", stdin);
    scanf("%d%d%d", &H, &W, &N);
    root = buf[bn++].alloc(0, 0, H, W, 0);
     
    for (int i = 0; i < N; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        root->push(x, y, buf);
    }
    root->area();
    printf("%d %d\n", maxAns, minAns);
    return 0;
}