//fail: segmantation fault
//http://jungol.co.kr/bbs/board.php?bo_table=pbank&wr_id=2425&sca=50
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>
#include <string.h>

const int ALPHABET_NUM  = 26 + 1;
const int INDICATOR_NUM = 1 + 1;
const int STRING_NUM    = 9 + 1;
const int MAX_NUM       = 9000;
const int ONE_BASED     = 1;

int getNum(char ch)
{
    return ch - 'A';
}
class Node
{
private:
    Node* m_pChild[ALPHABET_NUM];
    int m_cnt;

public:
    Node()
    {
        memset(m_pChild, 0, sizeof(m_pChild));
        m_cnt = 0;
    }
    Node** getChildArr()
    {
        return m_pChild;
    }
    void upCounting()
    {
        m_cnt++;
    }
    int getCount()
    {
        return m_cnt;
    }
};

Node g_notUsedNode[MAX_NUM];

class Trie
{
private:
    Node m_head;
    int m_usedNodeCnt;

public:
    Trie()
    {
        m_usedNodeCnt = 0;
    }
    Node* getHeadAddr()
    {
        return &m_head;
    }
    Node* _allocate(char ch)
    {
        assert(m_usedNodeCnt < MAX_NUM);
        return &g_notUsedNode[m_usedNodeCnt++];
    }

    /*
    NULL문자인 경우,(삽입완료됐다면)
        return한다.

    NULL문자가 아닌 경우,
        child중에 해당 문자가 없는 경우,
            child에 해당 문자를 가지는 node를 할당한다.
        child중에 해당 문자가 있는 경우,
            childNode에 count값을 upCounting한다.

    childNode, 다음문자에 대해서, 처음부터 반복한다.
    */
    void insert(char* str, Node* pNode)
    {
        char ch = *str;

        if (ch == NULL)
        {
            /* do nothing */
        }
        else
        {
            Node** childNode = &(pNode->getChildArr())[getNum(ch)];
            if (NULL == *childNode)
            {
                *childNode = _allocate(ch);
            }
            else
            {
                (*childNode)->upCounting();
            }

            insert(++str, *childNode);
        }
    }

    /*
    NULL문자인 경우,(search완료했다면)
        Node주소를 return한다.

    NULL문자가 아닌 경우,(찾고자 하는 string이 없는 경우)
        child중에 해당 문자가 없는 경우,
            NULL을 return한다.

    childNode, 다음문자에 대해서, 처음부터 반복한다.
    */
    Node* search(char* str, Node* pNode)
    {
        char ch = *str;

        if (ch == NULL)
        {
            return pNode;
        }
        else
        {
            Node* childNode = (pNode->getChildArr())[getNum(ch)];
            if (NULL == childNode)
            {
                return NULL;
            }
            search(++str, childNode);
        }
    }
};

int main()
{
    freopen("input.txt", "r", stdin);
    int testNum;
    scanf("%d", &testNum);

    for (int i = 0; i < testNum; i++)
    {
        //printf("i=%d\n", i);
        int cmdNum;
        scanf("%d", &cmdNum);
        Trie trie;
        memset(g_notUsedNode, 0, sizeof(g_notUsedNode));

        for (int j = 0; j < cmdNum; j++)
        {
            char indicator[INDICATOR_NUM];
            char string[STRING_NUM];
            scanf("%s", indicator);
            scanf("%s", string);
            //printf("\n%s %s\n", indicator, string);

            if ('I' == indicator[0])
            {
                trie.insert(string, trie.getHeadAddr());
            }
            else if ('O' == indicator[0])
            {
                Node* temp = trie.search(string, trie.getHeadAddr());
                if (NULL == temp)
                {
                    printf("0");
                }
                else
                {
                    printf("%d", temp->getCount() + ONE_BASED);
                }
                printf(" ");
            }
            else
            {
                assert(0);
            }
        }
        printf("\n");
    }
    return 0;
}