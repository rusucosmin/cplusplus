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
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct node {
    long long bestsum, best;
    node() {
        update(0LL);
    }
    void update(long long value) {
        bestsum = best = value;
    }
    void update(node Left, node Right) {
        bestsum = max(Left.bestsum, Right.bestsum);
        bestsum = max(bestsum, Left.best + Right.best);
        best = max(Left.best, Right.best);
    }
};

node arb[MAXN << 2];
int N, Q;

void Update(int Node, int st, int dr, int x, long long value) {
    if(st == dr) {
        arb[Node].update(value);
        return;
    }
    int mid = ((st + dr) >> 1);
    if(x <= mid)
        Update(2*Node, st, mid, x, value);
    else Update(2*Node + 1, mid + 1, dr, x, value);
    arb[Node].update(arb[2*Node], arb[2*Node + 1]);
}

node Query(int Node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b)
        return arb[Node];
    int mid =((st + dr) >> 1);
    node Left, Right;
    if(a <= mid)
        Left = Query(2*Node, st, mid, a, b);
    if(mid < b)
        Right = Query(2*Node + 1, mid + 1, dr, a, b);
    node Father;
    Father.update(Left, Right);
    return Father;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif // ONLINE_JUDGE
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++ i) {
        int x;
        scanf("%d", &x);
        Update(1, 1, N, i, 1LL * x);
    }
    scanf("%d", &Q);
    for(int i = 1 ; i <= Q ; ++ i) {
        char c[2];
        int x, y;
        scanf("%s %d %d", &c, &x, &y);
        //printf("%d %d\n", x, y);
        if(c[0] == 'U')
            Update(1, 1, N, x, y);
        else printf("%lld\n", Query(1, 1, N, x, y).bestsum);
    }
    return 0;
}
