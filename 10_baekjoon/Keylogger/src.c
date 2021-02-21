//https://www.acmicpc.net/problem/5397
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>

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

class List
{
private:
public:
    Node m_head;
    Node m_tail;

public:
    List()
    {
        m_head.m_pNext = &m_tail;
        m_tail.m_pPrev = &m_head;
    }

    Node* _allocNode(char ch)
    {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->ch = ch;
        return newNode;
    }

    void insertNode(Node* pNode, char ch)
    {
        assert(pNode != &m_tail);
        Node* newNode = _allocNode(ch);

        newNode->m_pPrev = pNode;
        newNode->m_pNext = pNode->m_pNext;

        pNode->m_pNext->m_pPrev = newNode;
        pNode->m_pNext = newNode;
        //return newNode;
    }

    void deleteNode(Node* pNode)
    {
        pNode->m_pPrev->m_pNext = pNode->m_pNext;
        pNode->m_pNext->m_pPrev = pNode->m_pPrev;
        free(pNode);
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
char string[MAX_STRLEN];
int main()
{
    freopen("input.txt", "r", stdin);

    int tcNum;
    scanf("%d", &tcNum);
    for (int i = 0; i < tcNum; i++)
    {
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
                if (&objList.m_head != cursorNode)
                {
                    cursorNode = cursorNode->m_pPrev;
                }
                break;

            case '>':
                if (objList.m_tail.m_pPrev != cursorNode)
                {
                    cursorNode = cursorNode->m_pNext;
                }
                break;

            case '-':
                if ((cursorNode != &objList.m_head) && (cursorNode != &objList.m_tail))
                {
                    Node* pPrev = cursorNode->m_pPrev;
                    objList.deleteNode(cursorNode);
                    cursorNode = pPrev;
                }
                break;

            default:
                objList.insertNode(cursorNode, string[j]);
                cursorNode = cursorNode->m_pNext;
                break;
            }
        }
        objList.printList();
    }
    return 0;
}