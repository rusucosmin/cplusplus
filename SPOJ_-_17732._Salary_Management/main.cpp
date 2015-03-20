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
#include <cassert>

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
    long long add;
    long long low;
    long long sum;
    bool lazy;
};

int T, N, M, K;
Graph G;
int salary[MAXN];
int in[MAXN], out[MAXN], Euler[MAXN];
node arb[MAXN * 4];

void DFs(int Node, int Father) {
    in[Node] = ++ K;
    Euler[K] = Node;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(*it == Father)
            continue;
        DFs(*it, Node);
    }
    out[Node] = K;
}

void Build(int Node, int st, int dr) {
    if(st == dr) {
        arb[Node].sum = 1LL * salary[Euler[st]];
        arb[Node].low = 1LL * salary[Euler[st]];
        arb[Node].lazy = 0;
        arb[Node].add = 0;
        return;
    }
    int mid = ((st + dr) >> 1);
    Build(2*Node, st, mid);
    Build(2*Node+1, mid+1, dr);
    arb[Node].sum = arb[2*Node].sum + arb[2*Node + 1].sum;
    arb[Node].low = min(arb[2*Node].low, arb[2*Node + 1].low);
    arb[Node].lazy = 0;
    arb[Node].add = 0;
}

void Update(int Node, int st, int dr, int a, int b, long long value) {
    if(a <= st && dr <= b) {
        arb[Node].lazy = 1;
        arb[Node].add += value;
        arb[Node].sum += (dr - st + 1) * value;
        arb[Node].low += value;
        return;
    }
    int mid = ((st + dr) >> 1);
    if(arb[Node].lazy) {
        Update(2*Node, st, mid, st, mid, arb[Node].add);
        Update(2*Node+1, mid + 1, dr, mid + 1, dr, arb[Node].add);
        arb[Node].lazy = 0;
        arb[Node].add = 0;
    }
    if(a <= mid)
        Update(2*Node, st, mid, a, b, value);
    if(mid < b)
        Update(2*Node + 1, mid + 1, dr, a, b, value);
    arb[Node].sum = arb[2*Node].sum + arb[2*Node + 1].sum;
    arb[Node].low = min(arb[2*Node].low, arb[2*Node + 1].low);
}

long long QueryMin(int Node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b)
        return min(1000LL, arb[Node].low);
    int mid = ((st + dr) >> 1);
    if(arb[Node].lazy) {
        Update(2*Node, st, mid, st, mid, arb[Node].add);
        Update(2*Node+1, mid + 1, dr, mid + 1, dr, arb[Node].add);
        arb[Node].lazy = 0;
        arb[Node].add = 0;
    }
    long long actMin = 1000LL;
    if(a <= mid)
        actMin = min(actMin, QueryMin(2*Node, st, mid, a, b));
    if(mid < b)
        actMin = min(actMin, QueryMin(2*Node + 1, mid + 1, dr, a, b));
    return actMin;
}

long long Query(int Node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b)
        return arb[Node].sum;
    int mid = ((st + dr) >> 1);
    if(arb[Node].lazy) {
        Update(2*Node, st, mid, st, mid, arb[Node].add);
        Update(2*Node + 1, mid + 1, dr, mid + 1, dr, arb[Node].add);
        arb[Node].lazy = 0;
        arb[Node].add = 0;
    }
    long long ans = 0;
    if(a <= mid)
        ans += Query(2*Node, st, mid, a, b);
    if(mid < b)
        ans += Query(2*Node + 1, mid + 1, dr, a, b);
    return ans;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif // ONLINE_JUDGE
    scanf("%d", &T);
    for(int test = 1 ; test <= T ; ++ test) {
        printf("Case %d:\n", test);
        scanf("%d %d", &N, &M);
        for(int i = 1 ; i <= N ; ++ i) {
            int x;
            scanf("%d %d", &x, &salary[i]);
            G[x].push_back(i);
            G[i].push_back(x);
        }
        DFs(1, 0);
        Build(1, 1, N);
        for(int i = 1 ; i <= M ; ++ i) {
            int op, x;
            scanf("%d%d", &op, &x);
            if(op == 1) {
                long long myans = Query(1, 1, N, in[x], out[x]);
                printf("%lld\n", Query(1, 1, N, in[x], out[x]));
            }
            else {
                long long actMin = QueryMin(1, 1, N, in[x], out[x]);
                actMin = min(actMin, 1000LL);
                Update(1, 1, N, in[x], out[x], actMin);
            }
        }
        for(int i = 0 ; i <= N ; ++ i)
            vector <int> ().swap(G[i]);
        K = 0;
    }
    return 0;
}
