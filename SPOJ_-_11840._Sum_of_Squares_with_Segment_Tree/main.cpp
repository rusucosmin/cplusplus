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
    int all;
    int add;
    int sum;
    int sqsum;
    bool lazysum;
    bool lazyall;
};

node arb[MAXN << 2];
int N, T, M;

void Update(int Node, int st, int dr, int pos, long long value) {
    if(st == dr) {
        arb[Node].sum = value;
        arb[Node].sqsum = value * value;
        return;
    }
    int mid = ((st + dr) >> 1);
    if(pos <= mid)
        Update(2*Node, st, mid, pos, value);
    else Update(2*Node + 1, mid + 1, dr, pos, value);
    arb[Node].sum = arb[2*Node].sum + arb[2*Node + 1].sum;
    arb[Node].sqsum = arb[2*Node].sqsum + arb[2*Node + 1].sqsum;
}

void Update(int Node, int st, int dr, int a, int b, long long value, bool how) {
    if(a <= st && dr <= b) {
        if(how) {
            arb[Node].lazyall = 1;
            arb[Node].lazysum = 0;
            arb[Node].sum = (dr - st + 1) * value;
            arb[Node].sqsum = (dr - st + 1) * value * value;
            arb[Node].all = value;
            arb[Node].add = 0;
        }
        else {
            arb[Node].lazysum = 1;
            arb[Node].lazyall = 0;
            arb[Node].all = 0;
            arb[Node].add += 1;
            arb[Node].sqsum += value * value * (dr - st + 1);
            arb[Node].sqsum += 2 * value * arb[Node].sum;
            arb[Node].sum += (dr - st + 1);
        }
        return;
    }
    int mid = ((st + dr) >> 1);
    if(arb[Node].lazysum) {
        Update(2*Node, st, mid, st, mid, arb[Node].add, 0);
        Update(2*Node + 1, mid + 1, dr, mid + 1, dr, arb[Node].add, 0);
        arb[Node].lazysum = 0;
        arb[Node].add = 0;
    }
    if(arb[Node].lazyall) {
        Update(2*Node, st, mid, st, mid, arb[Node].all, 1);
        Update(2*Node + 1, mid + 1, dr, mid + 1, dr, arb[Node].all, 1);
        arb[Node].lazyall = 0;
        arb[Node].all = 0;
    }
    if(a <= mid)
        Update(2*Node, st, mid, a, b, value, how);
    if(mid < b)
        Update(2*Node +1 , mid + 1, dr, a, b, value, how);
    arb[Node].sum = arb[2*Node].sum + arb[2*Node + 1].sum;
    arb[Node].sqsum = arb[2*Node].sqsum + arb[2*Node + 1].sqsum;
}

long long Query(int Node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b)
        return arb[Node].sqsum;
    int mid = ((st + dr) >> 1);
    if(arb[Node].lazysum) {
        Update(2*Node, st, mid, st, mid, arb[Node].add, 0);
        Update(2*Node + 1, mid + 1, dr, mid + 1, dr, arb[Node].add, 0);
        arb[Node].lazysum = 0;
        arb[Node].add = 0;
    }
    if(arb[Node].lazyall) {
        Update(2*Node, st, mid, st, mid, arb[Node].all, 1);
        Update(2*Node + 1, mid + 1, dr, mid + 1, dr, arb[Node].all, 1);
        arb[Node].lazyall = 0;
        arb[Node].all = 0;
    }
    long long sum = 0;
    if(a <= mid)
        sum += Query(2*Node, st, mid, a, b);
    if(mid < b)
        sum += Query(2*Node + 1, mid + 1, dr, a, b);
    return sum;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif // ONLINE_JUDGE
    scanf("%d", &T);
    for(int test = 1 ; test <= T ; ++ test) {
        printf("Case %d:\n", test);
        scanf("%d%d", &N, &M);
        for(int i = 1 ; i <= N ; ++ i) {
            int x;
            scanf("%d", &x);
            Update(1, 1, N, i, 1LL * x);
        }
        for(int i = 1 ; i <= M ; ++ i) {
            int op, x, y, z;
            scanf("%d%d%d", &op, &x, &y);
            if(op == 0) {
                scanf("%d", &z);
                Update(1, 1, N, x, y, 1LL * z, 1);
            }
            if(op == 1) {
                scanf("%d", &z);
                Update(1, 1, N, x, y, 1LL * z, 0);
            }
            if(op == 2)
                printf("%lld\n", Query(1, 1, N, x, y));
        }
    }
    fin.close();
    fout.close();
    return 0;
}
