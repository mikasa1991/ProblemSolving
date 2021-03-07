// http://jungol.co.kr/xpert/contestproblem.php?bo_table=prelearning&cid=1475&pid=7&al=005004&stx=7
// 파티일정관리2
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>

// [0][2]: 2018년 1월까지의 day누적값
int gDayStackedTable[100 + 1][12 + 1];
struct Date
{
    int year;
    int month;
    int day;
    void setter(int y, int m, int d)
    {
        year = y;
        month = m;
        day = d;
    }
    int getDay()
    {
        int day[12 + 1] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if ((0 == year % 400) || ((0 == year % 4) && (0 != year % 100)))
        {
            day[2] = 29;
        }

        return day[month];
    }
    int getKey()
    {
        //assert(year >= 2018 && year <= 2117);
        //assert(month >= 1 && month <= 12);
        //assert(day >= 1 && day <= 31);
        return gDayStackedTable[year - 2018][month] + day;
    }
};

void initDayStackedTb()
{
    int sum = 0;
    for (int i = 0; i < 100; i++)
    {
        for (int j = 1; j < (12 + 1); j++)
        {
            Date date;
            date.setter(i + 2018, j, 0);
            gDayStackedTable[i][j] = sum;
            sum += date.getDay();
        }
    }
}

struct Node
{
    int data; //id or dateKey
    Node* prev;
    Node* next;
    Node* addr;

    Node* alloc(int _data, Node* _addr)
    {
        data = _data;
        prev = NULL;
        next = NULL;
        addr = _addr;
        return this;
    }

    void del()
    {
        next->prev = prev;
        prev->next = next;
    }
};

Node gBuf[1000000];
int gBufCnt;

struct List
{
    Node head;
    Node tail;
    int cnt;

    void init()
    {
        cnt = 0;

        head.prev = NULL;
        tail.next = NULL;

        head.next = &tail;
        tail.prev = &head;
    }

    void push(int data, Node* addr)
    {
        Node* newNode = gBuf[gBufCnt++].alloc(data, addr);
        newNode->prev = &head;
        newNode->next = head.next;
        head.next->prev = newNode;
        head.next = newNode;
        cnt++;
    }

    int pop()
    {
        int retId = head.next->data;
        head.next->addr->del();
        head.next->del();
        cnt--;
        return retId;
    }

    void downCounting()
    {
        assert(cnt > 0);
        cnt--;
    }

    bool isEmpty()
    {
        return (0 == cnt);
    }
};

List gDateTable[40010];
List gIdTable[10010];

void reserve()
{
    int id;
    int method;
    int cnt;
    Date date;
    scanf("%d%d%d", &id, &method, &cnt);
    scanf("%4d%2d%2d", &date.year, &date.month, &date.day);

#define MONTH_CYCLE   (8)
#define YEAR_CYCLE    (9)
#define DEC           (12)
#define JAN           (1)
#define LAST_DATE_KEY (gDayStackedTable[99][12] + 31)
    int dateKey = date.getKey();
    for (int i = 1; i <= cnt; i++)
    {
        gDateTable[dateKey].push(id, &gBuf[gBufCnt + 1]);
        gIdTable[id].push(dateKey, &gBuf[gBufCnt - 1]);

        if (0 == method) break;

        if (YEAR_CYCLE == method)
        {
            date.year += 1;
            dateKey = date.getKey();
        }
        else if (MONTH_CYCLE == method)
        {
            if (DEC == date.month)
            {
                date.year += 1;
                date.month = JAN;
            }
            else
            {
                date.month += 1;
            }

            dateKey = date.getKey();
        }
        else
        {
            dateKey += method;
        }

        if ((date.year > 2117) || (dateKey > LAST_DATE_KEY)) break;
    }
    return;
}

void cancel()
{
    int method;
    scanf("%d", &method);
    if (2 == method)
    {
        int id;
        scanf("%d", &id);

        while (false == gIdTable[id].isEmpty())
        {
            int dateKey = gIdTable[id].pop();
            gDateTable[dateKey].downCounting();
        }
    }
    else
    {
        Date date;
        scanf("%4d%2d%2d", &date.year, &date.month, &date.day);
        int dateKey = date.getKey();

        while (false == gDateTable[dateKey].isEmpty())
        {
            int id = gDateTable[dateKey].pop();
            gIdTable[id].downCounting();

            if (method == 1)
            {
                while (false == gIdTable[id].isEmpty())
                {
                    int dateKey = gIdTable[id].pop();
                    gDateTable[dateKey].downCounting();
                }
            }
        }
    }
}

void output()
{
    Date date;
    scanf("%4d%2d%2d", &date.year, &date.month, &date.day);
    int dateKey = date.getKey();

    int sum = 0;
    for (int i = 0; (i < 30) && (i <= LAST_DATE_KEY); i++)
    {
        sum += gDateTable[dateKey + i].cnt;
    }
    printf("%d\n", sum);
}

void init()
{
    gBufCnt = 0;
    for (int i = 0; i < 10010; i++)
    {
        gIdTable[i].init();
    }
    for (int i = 0; i < 40010; i++)
    {
        gDateTable[i].init();
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    int tc;
    scanf("%d", &tc);
    initDayStackedTb();

    for (int i = 0; i < tc; i++)
    {
        init();
        int cmdCnt;
        scanf("%d", &cmdCnt);

        for (int j = 0; j < cmdCnt; j++)
        {
            int mode;
            scanf("%d", &mode);
            switch (mode)
            {
            case 1:
                reserve();
                break;
            case 2:
                cancel();
                break;
            case 3:
                output();
                break;
            default:
                break;
            }
        }
    }
    return 0;
}