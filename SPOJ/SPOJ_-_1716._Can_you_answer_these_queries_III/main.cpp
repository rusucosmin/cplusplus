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

const char infile[] = "input.in";
const char outfile[] = "output.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const long long oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct node {
    long long best, pref, suf, sum;
    node () {
        Update(-oo);
    }
    void Update(long long value) {
        best = value;
        pref = value;
        suf = value;
        sum = value;
    }
    void Update(node Left, node Right) {
        sum = Left.sum + Right.sum;
        pref = max(Left.pref, Left.sum + Right.pref);
        suf = max(Right.suf, Right.sum + Left.suf);
        best = max(Left.best, Right.best);
        best = max(best, Left.suf + Right.pref);
    }
};

node arb[MAXN << 2];
int N, M;
long long a[MAXN];

void Build(int Node, int st, int dr) {
    if(st == dr) {
        arb[Node].Update(a[st]);
        return;
    }
    int mid = ((st + dr) >> 1);
    Build(2*Node, st, mid);
    Build(2*Node+1, mid+1, dr);
    arb[Node].Update(arb[2*Node], arb[2*Node + 1]);
}

void Update(int Node, int st, int dr, int pos) {
    if(st == dr) {
        arb[Node].Update(a[pos]);
        return;
    }
    int mid = ((st + dr) >> 1);
    if(pos <= mid)
        Update(2*Node, st, mid, pos);
    else Update(2*Node + 1, mid + 1, dr, pos);
    arb[Node].Update(arb[2*Node], arb[2*Node + 1]);
}

node Query(int Node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b)
        return arb[Node];
    int mid = ((st + dr) >> 1);
    node Left, Right, father;
    if(a <= mid)
        Left = Query(2*Node, st, mid, a, b);
    if(mid < b)
        Right = Query(2*Node + 1, mid + 1, dr, a, b);
    father.Update(Left, Right);
    return father;
}

int main() {

    cin >> N;
    for(int i = 1 ; i <= N ; ++ i)
        cin >> a[i];
    Build(1, 1, N);
    cin >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int op, x, y;
        cin >> op >> x >> y;
        if(op == 0) {
            a[x] = 1LL * y;
            Update(1, 1, N, x);
        }
        if(op == 1)
            cout << Query(1, 1, N, x, y).best << '\n';
    }
    return 0;
}
