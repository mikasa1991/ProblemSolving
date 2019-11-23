/**************************************************************
    Problem: 3107
    User: dong_hee.lee
    Language: C++
    Result: Success
    Time:71 ms
    Memory:5436 kb
****************************************************************/
 
 
//(정올 실전문제 : 3107) CD홀더
/// *** user.cpp ***
#ifndef NULL
#define NULL 0
#endif
#define MAXN ((int)1e5 + 10)
#define MAXT (1 << 18)//N보다 크거나 같은 2의 제곱수의 2배 공간 필요(2^17이 12만정도이므로 2^18 필요)
enum { LEFT, RIGHT };
enum { MAXEMPYT = -MAXN, MINEMPTY = MAXN, SEQEMPTY = (int)1e5 };
int lastn;//CD홀더 마지막 번호
int hpos;//헤더위치
int hdir;//헤더방향
int seq;//삽입된 순서용
int cdseq[MAXN];//각 CD가 삽입된 순서
int maxtree[MAXT];//삽입된 cd중 번호가 제일 큰 cd
int mintree[MAXT];//삽입된 cd중 번호가 제일 작은 cd
int seqtree[MAXT];//삽입된 cd중 제일 먼저 삽입된 cd
void InitTree(int n, int s, int e) {
    maxtree[n] = MAXEMPYT; mintree[n] = MINEMPTY; seqtree[n] = SEQEMPTY;
    if (s == e) return;
    int L = n * 2, R = L + 1, m = (s + e) / 2;
    InitTree(L, s, m); InitTree(R, m + 1, e);
}
inline int MAXIDX(int a, int b) { return (a > b) ? a : b; }
inline int MINIDX(int a, int b) { return (a < b) ? a : b; }
inline int MINSEQ(int a, int b) { return (cdseq[a] < cdseq[b]) ? a : b; }
void update(int n, int s, int e, int idx, int mode) {
    if (s == e) {//leaf node
        if (mode) {//추가
            maxtree[n] = mintree[n] = seqtree[n] = idx;//삽입되었으므로 인덱스 저장
            cdseq[idx] = ++seq;//삽입순서 저장
        }
        else {//제거
            maxtree[n] = MAXEMPYT; mintree[n] = MINEMPTY; seqtree[n] = SEQEMPTY;
        }
        return;
    }
    int L = n * 2, R = L + 1, m = (s + e) / 2;
    if (idx > m) update(R, m + 1, e, idx, mode);
    else update(L, s, m, idx, mode);
    maxtree[n] = MAXIDX(maxtree[L], maxtree[R]);
    mintree[n] = MINIDX(mintree[L], mintree[R]);
    seqtree[n] = MINSEQ(seqtree[L], seqtree[R]);
}
int maxquery(int n, int s, int e, int qs, int qe) {
    if ((qe < s) || (e < qs)) return MAXEMPYT;
    if ((qs <= s) && (e <= qe)) return maxtree[n];
    int L = n * 2, R = L + 1, m = (s + e) / 2;
    return MAXIDX(maxquery(L, s, m, qs, qe), maxquery(R, m + 1, e, qs, qe));
}
int minquery(int n, int s, int e, int qs, int qe) {
    if ((qe < s) || (e < qs)) return MINEMPTY;
    if ((qs <= s) && (e <= qe)) return mintree[n];
    int L = n * 2, R = L + 1, m = (s + e) / 2;
    return MINIDX(minquery(L, s, m, qs, qe), minquery(R, m + 1, e, qs, qe));
}
void init(int holder_size, int head) {//번호가 0번 부터임을 주의
    lastn = holder_size - 1; hpos = head; hdir = LEFT; seq = 0;
    cdseq[SEQEMPTY] = MAXN;
    InitTree(1, 0, lastn);//빈 상태 만들기
}
void insert(int holder) {
    update(1, 0, lastn, holder, 1);
}
int first() {
    hpos = seqtree[1];//제일 먼저 삽입된 CD
    update(1, 0, lastn, hpos, 0);//해당 CD 제거
    return hpos;
}
int near() {
    int left = maxquery(1, 0, lastn, 0, hpos);//헤더 위치 왼쪽에서 삽입된 CD중 제일 큰 번호
    int right = minquery(1, 0, lastn, hpos, lastn);//헤더 위치 오른쪽에서 삽입된 CD중 제일 작은 번호
    if ((right == MINEMPTY) || ((hpos - left) <= (right - hpos))) hpos = left;
    else hpos = right;
    update(1, 0, lastn, hpos, 0);//해당 CD 제거
    return hpos;
}
int forward() {
    if (hdir == LEFT) {
        hpos = maxquery(1, 0, lastn, 0, hpos);
        if (hpos == MAXEMPYT) {//왼쪽에 CD없음
            hdir = RIGHT; hpos = mintree[1];//방향 전환
        }
    }
    else {
        hpos = minquery(1, 0, lastn, hpos, lastn);
        if (hpos == MINEMPTY) {//왼쪽에 CD없음
            hdir = LEFT; hpos = maxtree[1];//방향 전환
        }
    }
    update(1, 0, lastn, hpos, 0);//해당 CD 제거
    return hpos;
}
int left() {
    hpos = maxquery(1, 0, lastn, 0, hpos);
    if (hpos == MAXEMPYT) hpos = maxtree[1];
    update(1, 0, lastn, hpos, 0);//해당 CD 제거
    return hpos;
}
int right() {
    hpos = minquery(1, 0, lastn, hpos, lastn);
    if (hpos == MINEMPTY) hpos = mintree[1];
    update(1, 0, lastn, hpos, 0);//해당 CD 제거
    return hpos;
}