//https://www.acmicpc.net/problem/19237

#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>

/*
입력받기
냄새 뿌린다.

1초마다
존재하는 냄새 지속시간를 1초 줄이고, 0초가 된 냄새는 삭제한다.
상어가 다음 좌표로 이동하고, 냄새 뿌린다.
1번 상어만 남아있다면 걸린 시간을 출력하고 프로그램을 종료한다.
1000초가 지났다면, -1을 출력하고 프로그램을 종료한다.
 */

#define MAX_MAPSIZE     (20 + 1)
#define MAX_SHARK_CNT   (MAX_MAPSIZE*MAX_MAPSIZE)
#define DIR_CNT         (4)
#define UP      1
#define DOWN    2
#define LEFT    3
#define RIGHT   4

typedef struct _MapInfo
{
    int sharkId;
    int smellId;
    int smellTime;
}MapInfo;

typedef struct _Position
{
    int row;
    int col;
    int dir;
}Position;

typedef struct _SharkInfo
{
    bool bDeath;
    Position posi;
    int table[DIR_CNT + 1/*상어방향*/][DIR_CNT + 1];
}SharkInfo;

//UP DOWN LEFT RIGHT
const int dr[DIR_CNT + 1] = { 0,  -1,   1,   0,   0 };
const int dc[DIR_CNT + 1] = { 0,   0,   0,  -1,   1 };

int gMapSize, gSharkCnt, gSmellTime;
MapInfo gMap[MAX_MAPSIZE][MAX_MAPSIZE];
SharkInfo gShark[MAX_SHARK_CNT];

void SmellShot(int id, Position* posi)
{
    gMap[posi->row][posi->col].smellId = id;
    gMap[posi->row][posi->col].smellTime = gSmellTime;
}

void PrintMap()
{
    printf("print map\n");
    for (int r = 0; r < gMapSize; r++)
    {
        for (int c = 0; c < gMapSize; c++)
        {
            printf("(%d,%d,%d) ", gMap[r][c].sharkId, gMap[r][c].smellId, gMap[r][c].smellTime);
        }
        puts("");
    }
}
void PrintSharkInfo()
{
    printf("shark info\n");
    for (int i = 1; i <= gSharkCnt; i++)
    {
        printf("%d: r=%d,c=%d,d=%d\n", i, gShark[i].posi.row, gShark[i].posi.col, gShark[i].posi.dir);
    }
}
void PrintSharkDirTable()
{
    for (int i = 1; i <= gSharkCnt; i++)
    {
        printf("id=%d\n", i);
        for (int r = 1; r <= DIR_CNT; r++)
        {
            for (int c = 1; c <= DIR_CNT; c++)
            {
                printf("%d ", (gShark[i].table)[r][c]);
            }
            puts("");
        }
    }
}
void Init()
{
    scanf("%d%d%d", &gMapSize, &gSharkCnt, &gSmellTime);
    for (int r = 0; r < gMapSize; r++)
    {
        for (int c = 0; c < gMapSize; c++)
        {
            scanf("%d", &gMap[r][c].sharkId);
            if (0 != gMap[r][c].sharkId)
            {
                gShark[gMap[r][c].sharkId].posi.row = r;
                gShark[gMap[r][c].sharkId].posi.col = c;
                SmellShot(gMap[r][c].sharkId, &gShark[gMap[r][c].sharkId].posi);
            }
        }
    }
    //PrintMap();

    for (int i = 1; i <= gSharkCnt; i++)
    {
        scanf("%d", &gShark[i].posi.dir);
    }
    //PrintSharkInfo();

    for (int i = 1; i <= gSharkCnt; i++)
    {
        for (int r = 1; r <= DIR_CNT; r++)
        {
            for (int c = 1; c <= DIR_CNT; c++)
            {
                scanf("%d", &(gShark[i].table)[r][c]);
            }
        }
    }
    //PrintSharkDirTable();
}
void UpdateSmell()
{
    for (int r = 0; r < gMapSize; r++)
    {
        for (int c = 0; c < gMapSize; c++)
        {
            if (0 != gMap[r][c].smellId)
            {
                gMap[r][c].smellTime--;
                if (0 == gMap[r][c].smellTime)
                {
                    gMap[r][c].smellId = 0;
                }
            }
        }
    }
}
bool IsInArea(int r, int c)
{
    return r >= 0 && r < gMapSize && c >= 0 && c < gMapSize;
}
bool IsExistNoSmell(int id, Position* pPosi)
{
    Position curPosi = gShark[id].posi;
    for (int i = 1; i <= DIR_CNT; i++)
    {
        int idxDir = (gShark[id].table)[curPosi.dir][i];
        pPosi->row = curPosi.row + dr[idxDir];
        pPosi->col = curPosi.col + dc[idxDir];
        if (IsInArea(pPosi->row, pPosi->col) && 0 == gMap[pPosi->row][pPosi->col].smellId)
        {
            pPosi->dir = idxDir;
            return true;
        }
    }
    return false;
}
bool IsExistMySmell(int id, Position* pPosi)
{
    Position curPosi = gShark[id].posi;
    for (int i = 1; i <= DIR_CNT; i++)
    {
        int idxDir = (gShark[id].table)[curPosi.dir][i];
        pPosi->row = curPosi.row + dr[idxDir];
        pPosi->col = curPosi.col + dc[idxDir];
        if (IsInArea(pPosi->row, pPosi->col) && id == gMap[pPosi->row][pPosi->col].smellId)
        {
            pPosi->dir = idxDir;
            return true;
        }
    }
    return false;
}
int main()
{
    freopen("input.txt", "r", stdin);
    Init();

    int deathCnt = 0;
    for (int t = 1; t < 1001; t++)
    {
        //상어를 1번부터 이동시킨다.
        for (int id = 1; id <= gSharkCnt; id++)
        {
            //죽은 상어는 스킵한다.
            //상어의 다음 좌표를 결정한다.
            //다음 좌표에 다른 상어(자기보다 번호 작은)가 있을 경우, 해당 상어는 죽는다.
            //없을 경우, 해당 상어와 맵을 업데이트한다. 냄새 뿌리기.
            if (gShark[id].bDeath) continue;
            Position nextPosi;
            if (IsExistNoSmell(id, &nextPosi))
            {
                /*do nothing*/
            }
            else if (IsExistMySmell(id, &nextPosi))
            {
                /*do nothing*/
            }
            else
            {
                //printf("CanNotGoToAnywhere\n");
                assert(0);
                continue;
            }

            if (0 != gMap[nextPosi.row][nextPosi.col].sharkId)
            {
                //assert(id > gMap[nextPosi.row][nextPosi.col].sharkId);    //다음 t에서 이동할 때, 문제가 발생한다. 예를 들어 1번 상어가 4번 상어가 위치한 곳으로 이동하려 할 수 있거든.
                gMap[gShark[id].posi.row][gShark[id].posi.col].sharkId = 0;
                gShark[id].posi.row = -1;
                gShark[id].posi.col = -1;
                gShark[id].posi.dir = -1;
                gShark[id].bDeath = 1;
                deathCnt++;
            }
            else
            {
                //update map
                Position curPosi = gShark[id].posi;
                gMap[curPosi.row][curPosi.col].sharkId = 0;
                gMap[nextPosi.row][nextPosi.col].sharkId = id;
                //update sharkinfo
                gShark[id].posi = nextPosi;
            }
        }
        UpdateSmell();
        for (int id = 1; id <= gSharkCnt; id++)
        {
            if (1 == gShark[id].bDeath) continue;
            SmellShot(id, &gShark[id].posi);
        }
        //PrintMap();
        //PrintSharkInfo();
        if ((deathCnt == gSharkCnt - 1) && (0 == gShark[1].bDeath))
        {
            printf("%d", t);
            return 0;
        }
    }
    printf("%d", -1);
    return 0;
}