// http://jungol.co.kr/xpert/contestproblem.php?bo_table=prelearning&cid=1475&pid=3&al=005004&stx=3
// No. C : 마법색종이
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>

#define WHITE 0
#define BLACK 1

#define MAX(a,b) ((a > b) ? a : b)
#define MIN(a,b) ((a < b) ? a : b)
int ROW;
int COL;
int N;
class Node
{
public:
    int sRow;
    int sCol;
    int eRow;
    int eCol;
    int color;
    Node* leftChild;
    Node* rightChild;

    Node()
    {
        sRow = sCol = eRow = eCol = color = 0;
        leftChild = rightChild = NULL;
    }
    void setter(int sr, int sc, int er, int ec, int clr)
    {
        sRow = sr;
        sCol = sc;
        eRow = er;
        eCol = ec;
        color = clr;
    }
};

Node gAllocNode[60000 + 10];
int gUsedCnt;
int gMaxArea;
int gMinArea;

Node* allocNode(int sr, int sc, int er, int ec, int clr)
{
    Node* newNode = &gAllocNode[gUsedCnt++];
    newNode->setter(sr, sc, er, ec, clr);
    return newNode;
}

class Tree
{
public:
    Node root;

    void update(Node* pNode)
    {
        if (NULL == pNode->leftChild)
        {
            int area = (pNode->eRow - pNode->sRow) * (pNode->eCol - pNode->sCol);
            gMaxArea = MAX(area, gMaxArea);
            gMinArea = MIN(area, gMinArea);
        }
        else
        {
            update(pNode->leftChild);
            update(pNode->rightChild);
        }
    }

    Node* findLeafNode(Node* pNode, int r, int c)
    {
        Node* retNode = NULL;

        if (NULL == pNode->leftChild)
        {
            retNode = pNode;
        }
        else
        {
            if (r > pNode->leftChild->sRow && r < pNode->leftChild->eRow
                && c > pNode->leftChild->sCol && c < pNode->leftChild->eCol)
            {
                retNode = findLeafNode(pNode->leftChild, r, c);
            }
            else
            {
                retNode = findLeafNode(pNode->rightChild, r, c);
            }
        }
        return retNode;
    }
};

int main()
{
    freopen("input.txt", "r", stdin);
    scanf("%d%d%d", &ROW, &COL, &N);

    Tree tree;
    tree.root.setter(0, 0, ROW, COL, WHITE);
    gMaxArea = 0;
    gMinArea = ROW * COL;

    for (int i = 0; i < N; i++)
    {
        int row, col;
        scanf("%d%d", &row, &col);

        Node* ln = tree.findLeafNode(&tree.root, row, col);

        if (WHITE == ln->color)
        {
            ln->leftChild = allocNode(ln->sRow, ln->sCol, ln->eRow, col, BLACK);
            ln->rightChild = allocNode(ln->sRow, col, ln->eRow, ln->eCol, BLACK);
        }
        else // BLACK == leafNode->color
        {
            ln->leftChild = allocNode(ln->sRow, ln->sCol, row, ln->eCol, WHITE);
            ln->rightChild = allocNode(row, ln->sCol, ln->eRow, ln->eCol, WHITE);
        }
    }

    tree.update(&tree.root);
    printf("%d %d", gMaxArea, gMinArea);
    return 0;
}