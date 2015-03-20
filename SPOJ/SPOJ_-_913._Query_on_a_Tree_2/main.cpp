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

const int MAXN = 10005;
const int MAXL = 25;
const int oo = 0x3f3f3f3f;

typedef vector<pair<int, int> > Graph[MAXN];
typedef vector<pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int T, N, depth[MAXN], dp[MAXN], ancestor[MAXL][MAXN];
Graph G;

void DFs(int Node, int father, int actLevel) {
    depth[Node] = actLevel;
    ancestor[0][Node] = father;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(it->first == father)
            continue;
        dp[it->first] = dp[Node] + it->second;
        DFs(it->first, Node, actLevel + 1);
    }
}

int LCA(int x, int y) {
    if(depth[x] < depth[y])
        swap(x, y);
    int log1, log2;
    for(log1 = 1 ; (1 << log1) < depth[x] ; ++ log1);
    for(log2 = 1 ; (1 << log2) < depth[y] ; ++ log2);
    for(int k = log1 ; k >= 0 ; -- k)
        if(depth[x] - (1 << k) >= depth[y])
            x = ancestor[k][x];
    if(x == y)
        return x;
    for(int k = log2 ; k >= 0 ; -- k)
        if(ancestor[k][x] && ancestor[k][x] != ancestor[k][y]) {
            x = ancestor[k][x];
            y = ancestor[k][y];
        }
    return ancestor[0][x];
}

inline int QueryDistance(int x, int y) {
    int lca = LCA(x, y);
    return dp[x] + dp[y] - 2*dp[lca];
}

inline int KthAncestor(int x, int y) {
    if(!y)
        return x;
    for(int i = 0 ; (1 << i) <= y ; ++ i)
        if(y & (1 << i))
            x = ancestor[i][x];
    return x;
}

inline int QueryKth(int x, int y, int k) {
    int lca = LCA(x, y);
    if(depth[x] - depth[lca] + 1 < k) {
        k = (depth[x] + depth[y] - 2*depth[lca] + 1) - k + 1;
        swap(x, y);
    }
    -- k;
    return KthAncestor(x, k);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif // ONLINE_JUDGE
    scanf("%d", &T);
    for(int test = 1 ; test <= T ; ++ test) {
        scanf("%d", &N);
        for(int i = 1 ; i != N ; ++ i) {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            G[x].push_back(make_pair(y, z));
            G[y].push_back(make_pair(x, z));
        }
        DFs(1, 0, 1);
        for(int i = 1 ; (1 << i) <= N ; ++ i)
            for(int j = 1 ; j <= N ; ++ j)
                ancestor[i][j] = ancestor[i - 1][ancestor[i - 1][j]];
        char s[10];
        int x, y, k;
        while(scanf("%s", &s)) {
            if(s[1] == 'O')
                break;
            if(s[1] == 'I') {
                scanf("%d %d", &x, &y);
                printf("%d\n", QueryDistance(x, y));
            }
            if(s[1] == 'T') {
                scanf("%d %d %d", &x, &y, &k);
                printf("%d\n", QueryKth(x, y, k));
            }
        }
        for(int i = 1 ; i <= N ; ++ i)
            vector <pair<int, int> > ().swap(G[i]);
    }
    return 0;
}
