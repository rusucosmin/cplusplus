/*
    Complexity: O(M * C * log(N))
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>

using namespace std;

const char infile[] = "color4.in";
const char outfile[] = "color4.out";

const int MAXN = 50005;
const int MAXC = 76;
const int oo = 0x3f3f3f3f;
const int defcolor = 1;
const int lim = (1 << 10);

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

int N, M, C, K, in[MAXN], out[MAXN];
Graph G;

char buff[lim];
int pos;

inline void get(int &x) {
    x = 0;
    while(!isdigit(buff[pos])) {
        if(++ pos == lim) {
            fread(buff, 1, lim, stdin);
            pos = 0;
        }
    }
    while(isdigit(buff[pos])) {
        x = x * 10 + buff[pos] - '0';
        if(++ pos == lim) {
            fread(buff, 1, lim, stdin);
            pos = 0;
        }
    }
}

struct node {
    int fr[MAXC], frmax, lazy;
    node () {
        memset(fr, 0, sizeof(fr));
        frmax = 0;
        lazy = 0;
    }
    void Update(node _left, node _right) {
        frmax = 0;
        for(int i = defcolor ; i <= C ; ++ i) {
            fr[i] = _left.fr[i] + _right.fr[i];
            if(fr[frmax] < fr[i])
                frmax = i;
        }
    }
} arb[MAXN << 2];

inline void DFs(int Node, int Father) {
    in[Node] = ++ K;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(*it != Father)
                DFs(*it, Node);
    out[Node] = K;
}

inline void Build(int Node, int st, int dr) {
    if(st == dr) {
        ++ arb[Node].fr[defcolor];
        arb[Node].frmax = defcolor;
        arb[Node].lazy = 0;
        return;
    }
    int mid = ((st + dr) >> 1);
    Build(Node << 1, st, mid);
    Build((Node << 1) | 1, mid+1, dr);
    arb[Node].fr[defcolor] = arb[Node << 1].fr[defcolor] + arb[(Node << 1) | 1].fr[defcolor];
    arb[Node].frmax = defcolor;
}

inline void lazyUpdate(int Node, int st, int dr, int color) {
    memset(arb[Node].fr, 0, sizeof(arb[Node].fr));
    arb[Node].fr[color] = (dr - st + 1);
    arb[Node].frmax = color;
    arb[Node].lazy = color;
}

inline void Update(int Node, int st, int dr, int a, int b, int color) {
    if(a <= st && dr <= b) {
        lazyUpdate(Node, st, dr, color);
        return;
    }
    int mid = ((st + dr) >> 1);
    if(arb[Node].lazy) {
        lazyUpdate(Node << 1, st, mid, arb[Node].lazy);
        lazyUpdate((Node << 1) | 1, mid+1, dr, arb[Node].lazy);
        arb[Node].lazy = 0;
    }
    if(a <= mid)
        Update(Node << 1, st, mid, a, b, color);
    if(mid < b)
        Update((Node << 1) | 1, mid+1, dr, a, b, color);
    arb[Node].Update(arb[Node << 1], arb[(Node << 1) | 1]);
}

inline node Query(int Node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b)
        return arb[Node];
    int mid = ((st + dr) >> 1);
    if(arb[Node].lazy) {
        lazyUpdate(Node << 1, st, mid, arb[Node].lazy);
        lazyUpdate((Node << 1) | 1, mid+1, dr, arb[Node].lazy);
        arb[Node].lazy = 0;
    }
    node _left, _right;
    if(a <= mid)
        _left = Query(Node << 1, st, mid, a, b);
    if(mid < b)
        _right = Query((Node << 1) | 1, mid+1, dr, a, b);
    node father;
    father.Update(_left, _right);
    return father;
}

///#define get(x) scanf("%d", &x)


int main() {
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    get(N); get(M); get(C);
    for(int i = 1 ; i < N ; ++ i) {
        int x, y;
        get(x);
        get(y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    DFs(1, 0);
    Build(1, 1, N);
    for(int i = 1 ; i <= M ; ++ i) {
        int op, x, c;
        get(op); get(x);
        if(op == 0) {
            get(c);
            Update(1, 1, N, in[x], out[x], c);
        }
        if(op == 1) {
            node ans = Query(1, 1, N, in[x], out[x]);
            printf("%d %d\n", ans.frmax, ans.fr[ans.frmax]);
        }
    }
    return 0;
}
