#include <stdio.h>
#define MAXN (500)
#define STRN (42)
#define CHILD (26)
#define CAR (0)
#define SPY (1)
char spyname[MAXN + 10][STRN];
struct car {
	int p, q, k;//원가, 초기대여비용, 주행1킬로미터당추가비용
}carinfo[MAXN + 10];
struct spy {
	int flag, rent, cost;//일관성여부, 대여여부(차번호), 총비용
}spyinfo[MAXN + 10];
typedef struct trie {
	int id, leaf;//배정된아이디, 종단노드
	struct trie *child[CHILD];
}TRIE;
TRIE *croot;//차
TRIE *sroot;//스파이
int NewId[2];//[0]차, [1]스파이 아이디 배정용
int nodeptr;
TRIE node[MAXN * STRN * 2];//차+스파이
TRIE *myalloc() {
	TRIE *p = &node[nodeptr++];
	p->id = 0; p->leaf = 1;
	for (int i = 0; i < CHILD; i++) p->child[i] = NULL;
	return p;
}
void init() {
	nodeptr = NewId[CAR] = NewId[SPY] = 0;
	croot = myalloc();
	sroot = myalloc();
	for (int i = 1; i <= MAXN; i++) {
		spyinfo[i].flag = 1; spyinfo[i].rent = 0; spyinfo[i].cost = 0;
	}
}
int calidx(char ch) { return ch - 'a'; }
int getkey(TRIE *p, char *str, int sel) {
	if (!*str) {
		if (!p->id) p->id = ++NewId[sel];//배정 안되었으면 새로 배정
		return p->id;
	}
	int idx = calidx(*str);
	if (!p->child[idx]) {
		p->child[idx] = myalloc();
		p->leaf = 0;
	}
	return getkey(p->child[idx], str + 1, sel);
}
void PRT(TRIE *p) {
	if (p->id) {//spy
		printf("%s ", spyname[p->id]);
		if (!spyinfo[p->id].flag || spyinfo[p->id].rent) printf("INCONSISTENT\n");
		else printf("%d\n", spyinfo[p->id].cost);
	}
	if (p->leaf) return;//종단노드면 리턴
	for (int i = 0; i < CHILD; i++) {//오름차순 방문
		if (!p->child[i]) continue;//생성안된 자식노드이므로 skip
		PRT(p->child[i]);
	}
}
void carpickup(int idx, char *cstr) {
	if (!spyinfo[idx].flag) return;//이미 일관성 없음
	if (spyinfo[idx].rent) {//이미 대여중
		spyinfo[idx].flag = 0; return;//일관성 없음으로 표시
	}
	spyinfo[idx].rent = getkey(croot, cstr, CAR);//해당차번호 찾아서 저장
	spyinfo[idx].cost += carinfo[spyinfo[idx].rent].q;//해당차 초기대여비용 누적합
}
void carreturn(int idx, int d) {
	if (!spyinfo[idx].flag) return;//이미 일관성 없음
	if (!spyinfo[idx].rent) {//대여중 아님
		spyinfo[idx].flag = 0; return;//일관성 없음으로 표시
	}
	spyinfo[idx].cost += carinfo[spyinfo[idx].rent].k * d;//추가비용누적합
	spyinfo[idx].rent = 0;//반납처리
}
void caraccident(int idx, int s) {
	if (!spyinfo[idx].flag) return;//이미 일관성 없음
	if (!spyinfo[idx].rent) {//대여중 아님
		spyinfo[idx].flag = 0; return;//일관성 없음으로 표시
	}
	spyinfo[idx].cost += (carinfo[spyinfo[idx].rent].p * s + 99) / 100;//올림처리, 사고비용처리
}
void solve() {
	int N, M; char carname[STRN];
	int t, p, q, k, d, s; char e;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {//차 정보
		scanf("%s %d %d %d", carname, &p, &q, &k);
		int idx = getkey(croot, carname, CAR);
		carinfo[idx].p = p; carinfo[idx].q = q; carinfo[idx].k = k;
	}
	for (int i = 0; i < M; i++) {//사건 기록
		scanf("%d %s %c", &t, spyname[NewId[SPY] + 1], &e);
		int idx = getkey(sroot, spyname[NewId[SPY] + 1], SPY);
		if (e == 'p') {//차 대여
			scanf("%s", carname);
			carpickup(idx, carname);
		}
		else if (e == 'r') {//차 반납
			scanf("%d", &d);
			carreturn(idx, d);
		}
		else {//차 사고
			scanf("%d", &s);
			caraccident(idx, s);
		}
	}
	PRT(sroot);//스파이 이름 오름차순 출력
}
int main() {
	int T;
#if 1
	freopen("input.txt", "r", stdin);
#endif
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		init();
		solve();
	}
	return 0;
}