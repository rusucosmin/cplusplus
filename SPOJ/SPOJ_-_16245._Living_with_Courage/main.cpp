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
    long long sum;
    long long low;
    node () {
        sum = 0;
        low = 0;
    }
};

int N, M;
node arb[MAXN << 2];

void Update(int Node, int st, int dr, int pos, int value) {
    if(st == dr) {
        arb[Node].sum += 1LL * value;
        arb[Node].low += 1LL * value;
        return;
    }
    int mid = ((st + dr) >> 1);
    if(pos <= mid)
        Update(2*Node, st, mid, pos, value);
    else Update(2*Node + 1, mid + 1, dr, pos, value);
    arb[Node].sum = arb[2*Node].sum + arb[2*Node + 1].sum;
    arb[Node].low = min(arb[2*Node].low, arb[2*Node + 1].low);
}

node Query(int Node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b)
        return arb[Node];
    int mid = ((st + dr) >> 1);
    long long sum = 0;
    node Left, Right;
    Left.low = oo;
    Right.low = oo;
    if(a <= mid)
        Left = Query(2*Node, st, mid, a, b);
    if(mid < b)
        Right = Query(2*Node + 1, mid + 1, dr, a, b);
    node Ret;
    Ret.sum = Left.sum + Right.sum;
    Ret.low = min(Left.low, Right.low);
    return Ret;
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
        Update(1, 1, N, i, x);
    }
    scanf("%d", &M);
    char a[10];
    int x;
    int y;
    for(int i = 1 ; i <= M ; ++ i) {
        scanf("%s%d%d", &a, &x, &y);
        if(a[0] == 'C') {
            ++ x;
            ++ y;
            node ans = Query(1, 1, N, x, y);
            printf("%lld\n", ans.sum - ans.low);
        }
        if(a[0] == 'G') {
            ++ y;
            Update(1, 1, N, y, x);
        }
        if(a[0] == 'E') {
            ++ y;
            Update(1, 1, N, y, -x);
        }
    }
    fin.close();
    fout.close();
    return 0;
}
