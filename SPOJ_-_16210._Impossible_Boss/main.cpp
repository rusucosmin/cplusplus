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
    long long sum, a1, r;
    bool lazy;
};

node arb[MAXN << 2];
int N, M;

long long arithProgSum(long long a1, long long r, int n) {
    return 1LL * n * (2 * a1 + r * (n - 1)) / 2;
}

void Update(int Node, long long a1, long long r, int n) {
    arb[Node].r += r;
    arb[Node].a1 += a1;
    arb[Node].lazy = 1;
    arb[Node].sum += arithProgSum(a1, r, n);
}

void Update(int Node, int st, int dr, int a, int b, long long r) {
    if(a <= st && dr <= b) {
        Update(Node, 1LL * (st - a + 1), r, dr - st + 1);
        return;
    }
    int mid = ((st + dr) >> 1);
    if(arb[Node].lazy) {
        Update(2*Node, arb[Node].a1, arb[Node].r, mid - st + 1);
        Update(2*Node + 1, arb[Node].a1 + (mid + 1 - st) * arb[Node].r, arb[Node].r, dr - mid);
        arb[Node].lazy = 0;
        arb[Node].a1 = 0;
        arb[Node].r = 0;
    }
    if(a <= mid)
        Update(2*Node, st, mid, a, b, r);
    if(mid < b)
        Update(2*Node + 1, mid + 1, dr, a, b, r);
    arb[Node].sum = arb[2*Node].sum + arb[2*Node + 1].sum;
}

long long Query(int Node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b)
        return arb[Node].sum;
    int mid = ((st + dr) >> 1);
    if(arb[Node].lazy) {
        Update(2*Node, arb[Node].a1, arb[Node].r, mid - st + 1);
        Update(2*Node + 1, arb[Node].a1 + (mid + 1 - st) * arb[Node].r, arb[Node].r, dr - mid);
        arb[Node].lazy = 0;
        arb[Node].a1 = 0;
        arb[Node].r = 0;
    }
    long long ret = 0;
    if(a <= mid)
        ret += Query(2*Node, st, mid, a, b);
    if(mid < b)
        ret += Query(2*Node + 1, mid + 1, dr, a, b);
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif // ONLINE_JUDGE
    scanf("%d%d", &N, &M);
    for(int i = 1 ; i <= M ; ++ i) {
        int op, x, y;
        scanf("%d%d%d", &op, &x, &y);
        if(op == 0)
            Update(1, 1, N, x, y, 1LL);
        else printf("%lld\n", Query(1, 1, N, x, y));
    }
    return 0;
}
