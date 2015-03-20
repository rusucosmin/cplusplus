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
    long long sum, add;
    bool lazy;
};

vector <node> arb;
int T, N, M;

void Update(int Node, int st, int dr, int a, int b, long long value) {
    if(a <= st && dr <= b) {
        arb[Node].sum += 1LL * value * (dr - st + 1);
        arb[Node].add += value;
        arb[Node].lazy = 1;
        return;
    }
    int mid = ((st + dr) >> 1);
    if(arb[Node].lazy == 1) {
        Update(2*Node, st, mid, st, mid, arb[Node].add);
        Update(2*Node + 1, mid + 1, dr, mid + 1, dr, arb[Node].add);
        arb[Node].lazy = 0;
        arb[Node].add = 0;
    }
    if(a <= mid)
        Update(2*Node, st, mid, a, b, value);
    if(mid < b)
        Update(2*Node + 1, mid + 1, dr, a, b, value);
    arb[Node].sum = arb[2*Node].sum + arb[2*Node + 1].sum;
}

long long Query(int Node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b)
        return arb[Node].sum;
    int mid = ((st + dr) >> 1);
    long long ret = 0;
    if(arb[Node].lazy == 1) {
        Update(2*Node, st, mid, st, mid, arb[Node].add);
        Update(2*Node + 1, mid + 1, dr, mid + 1, dr, arb[Node].add);
        arb[Node].lazy = 0;
        arb[Node].add = 0;
    }
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
    scanf("%d", &T);
    for(int test = 1 ; test <= T ; ++ test) {
        scanf("%d %d", &N, &M);
        arb.resize(4 * N);
        for(int i = 1 ; i <= M ; ++ i) {
            int op, x, y, z;
            scanf("%d", &op);
            switch(op) {
            case 0:
                scanf("%d %d %d", &x, &y, &z);
                Update(1, 1, N, x, y, 1LL * z);
                break;
            case 1:
                scanf("%d %d", &x, &y);
                printf("%lld\n", Query(1, 1, N, x, y));
                break;
            }
        }
        arb.clear();
    }
    return 0;
}
