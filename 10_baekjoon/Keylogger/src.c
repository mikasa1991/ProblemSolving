//https://www.acmicpc.net/problem/5397
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>
#include <string.h>

#define LEFT  1
#define RIGHT 2
static const int MAX_STRLEN = (int)1e6 + 10;

class Node
{
private:
public:
    char ch;
    Node* m_pPrev;
    Node* m_pNext;

public:
    Node()
    {
        ch = 0;
        m_pPrev = NULL;
        m_pNext = NULL;
    }
};

Node g_notUsedNode[MAX_STRLEN];

class List
{
private:
public:
    int m_usedNodeCnt;
    int m_cursor;
    Node m_head;
    Node m_tail;

public:
    List()
    {
        m_usedNodeCnt  = 0;
        m_cursor       = 0;
        m_head.m_pNext = &m_tail;
        m_tail.m_pPrev = &m_head;
    }

    Node* setCursor(Node* pNode, int param)
    {
        assert(pNode != &m_tail);

        Node* returnNode = pNode;

        if (LEFT == param)
        {
            if (pNode != &m_head)
            {
                returnNode = pNode->m_pPrev;
            }
        }
        else // (RIGHT == param)
        {
            if (pNode->m_pNext != &m_tail)
            {
                returnNode = pNode->m_pNext;
            }
        }
        return returnNode;
    }

    Node* _allocNode(char ch)
    {
        Node* newNode = &g_notUsedNode[m_usedNodeCnt++];
        newNode->ch = ch;
        return newNode;
    }

    Node* insertNode(Node* pNode, char ch)
    {
        assert(pNode != &m_tail);
        Node* newNode = _allocNode(ch);

        newNode->m_pPrev = pNode;
        newNode->m_pNext = pNode->m_pNext;

        pNode->m_pNext->m_pPrev = newNode;
        pNode->m_pNext          = newNode;
        return newNode;
    }

    Node* deleteNode(Node* pNode)
    {
        if (pNode == &m_head || pNode == &m_tail)
        {
            return pNode;
        }
        else
        {
            pNode->m_pPrev->m_pNext = pNode->m_pNext;
            pNode->m_pNext->m_pPrev = pNode->m_pPrev;
            return pNode->m_pPrev;
        }
    }

    void printList()
    {
        for (Node* temp = m_head.m_pNext; temp != &m_tail; temp = temp->m_pNext)
        {
            printf("%c", temp->ch);
        }
        printf("\n");
    }
};

int main()
{
    freopen("input.txt", "r", stdin);

    int tcNum;
    scanf("%d", &tcNum);
    for (int i = 0; i < tcNum; i++)
    {
        memset(g_notUsedNode, 0, sizeof(g_notUsedNode));

        char string[MAX_STRLEN];
        scanf("%s", string);
        int stringLen = strlen(string);
        //printf("%s %d\n", string, stringLen);
        
        List objList;
        Node* cursorNode = &objList.m_head;

        for (int j = 0; j < stringLen; j++)
        {
            //printf("%c\n", string[j]);
            switch (string[j])
            {
            case '<':
                cursorNode = objList.setCursor(cursorNode, LEFT);
                break;

            case '>':
                cursorNode = objList.setCursor(cursorNode, RIGHT);
                break;

            case '-':
                cursorNode = objList.deleteNode(cursorNode);
                break;

            default:
                cursorNode = objList.insertNode(cursorNode, string[j]);
                break;
            }
        }
        objList.printList();
    }
    return 0;
}