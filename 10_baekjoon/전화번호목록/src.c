//https://www.acmicpc.net/problem/5052
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>
#include <string.h>

const int MAX_NUM = (10000 + 10);
const int MAX_LEN = (10 + 1);
const int NUM_OF_CHILD = 10;
const int MAX_NODE = MAX_NUM * MAX_LEN;

int getNumtoChar(int ch)
{
    return (ch - '0');
}

typedef struct _Node
{
    int num;
    bool bTerminal;
    _Node* pChild[NUM_OF_CHILD];
    _Node()
    {
        num = -1;
        bTerminal = false;
        memset(pChild, 0, sizeof(pChild));
    }
}Node;
typedef struct _ArrOfNode
{
    int id;
    Node notUsedNode[MAX_NODE];

    void init()
    {
        id = 0;
        memset(notUsedNode, 0, sizeof(notUsedNode));
    }
    Node* allocNode(int num)
    {
        assert(id < MAX_NODE);
        Node* newNode = &notUsedNode[id++];
        newNode->num = num;
        return newNode;
    }
}ArrOfNode;
ArrOfNode gstArrOfNode;
typedef struct _Trie
{
    Node stHead;
    void insert(char* pStr, Node* pParent)
    {
        if (0 == *pStr)
        {
            pParent->bTerminal = true;
        }
        else
        {
            int num = getNumtoChar(*pStr);
            Node** ppChild = &(pParent->pChild)[num];
            if (NULL == *ppChild)
            {
                *ppChild = gstArrOfNode.allocNode(num);
            }
            insert(pStr + 1, *ppChild);
        }
    }

    bool haveAnotherPhoneNumber(char* pStr, Node* pParent)
    {
        if (0 == *pStr)
        {
            return false;
        }
        else
        {
            int num = getNumtoChar(*pStr);
            if ((true == (pParent->pChild)[num]->bTerminal) && (0 != *(pStr + 1)))
            {
                return true;
            }
            else
            {
                return haveAnotherPhoneNumber(pStr + 1, (pParent->pChild)[num]);
            }
        }
    }
}Trie;
int main()
{
    freopen("input.txt", "r", stdin);
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++)
    {
        int n;
        scanf("%d", &n);
        char string[MAX_NUM][MAX_LEN];
        gstArrOfNode.init();
        Trie stTrie;
        //input
        for (int j = 0; j < n; j++)
        {
            scanf("%s", string[j]);
            //printf("%s\n", string[j]);
            stTrie.insert(string[j], &stTrie.stHead);
        }

        //solve
        const char* pAns = "YES";
        for (int j = 0; j < n; j++)
        {
            if (stTrie.haveAnotherPhoneNumber(string[j], &stTrie.stHead))
            {
                pAns = "NO";
                break;
            }
        }
        printf("%s\n", pAns);
    }
    return 0;
}