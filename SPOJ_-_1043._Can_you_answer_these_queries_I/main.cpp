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

const int oo = 1 << 25;

struct node {
    int sum, pref, best, suf;
    node () {
        Update(-oo);
    }
    void Update(const int value) {
        sum = value;
        pref = value;
        best = value;
        suf = value;
    }
    void Update(const node Left, const node Right) {
        sum = Left.sum + Right.sum;
        pref = max(Left.pref, Left.sum + Right.pref);
        suf = max(Right.suf, Right.sum + Left.suf);
        best = max(Left.best, Right.best);
        best = max(best, Left.suf + Right.pref);
    }
};

node arb[1 << 19];
int N, M;

void Update(int Node, int st, int dr, int pos, int value) {
    if(st == dr) {
        arb[Node].Update(value);
        return;
    }
    int mid = ((st + dr) >> 1);
    if(pos <= mid)
        Update(2*Node, st, mid, pos, value);
    else Update(2*Node + 1, mid + 1, dr, pos, value);
    arb[Node].Update(arb[2*Node], arb[2*Node + 1]);
}

node Query(int Node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b)
        return arb[Node];
    int mid = ((st + dr) >> 1);
    node Left;
    node Right;
    if(a <= mid)
        Left = Query(2*Node, st, mid, a, b);
    if(mid < b)
        Right = Query(2*Node+1, mid+1, dr, a, b);
    node ret;
    ret.Update(Left, Right);
    return ret;
}

int main() {
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++ i) {
        int x;
        scanf("%d", &x);
        Update(1, 1, N, i, x);
    }
    scanf("%d", &M);
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%d\n", Query(1, 1, N, x, y).best);
    }
    return 0;
}
