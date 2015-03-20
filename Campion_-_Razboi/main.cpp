#include <fstream>
#include <vector>
#include <bitset>
#include <stdio.h>
#include <queue>
#include <string.h>

using namespace std;

const char infile[] = "razboi.in";
const char outfile[] = "razboi.out";

const int MAXN = 505;
const int oo = 0x3f3f3f3f;

typedef vector< pair<int, int> > Graph[MAXN];
typedef vector< pair<int, int> > :: iterator It;

int N, M;
int d[MAXN][MAXN], X, dp[MAXN];
bitset <MAXN> inQ, vis;
bitset <MAXN> Could;
Graph G;

inline bool BellmanFord(const int &startNode) {
    queue <int> Q;
    vis.reset();
    vis[startNode] = 1;
    inQ.reset();
    for(Q.push(startNode), d[startNode][startNode] = 0, inQ[startNode] = true ; !Q.empty() ; Q.pop() ) {
        int Node = Q.front();
        inQ[Node] = false;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
            int actNode = it->first;
            int cost = it->second;
            if(d[startNode][actNode] > d[startNode][Node] + cost) {
                d[startNode][actNode] = d[startNode][Node] + cost;
                vis[actNode] = true;
                if(!inQ[actNode]) {
                    Q.push(actNode);
                    inQ[actNode] = true;
                }
            }
        }
    }
    return vis.count() == N;
}

int main() {
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    scanf("%d %d", &N, &M);
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        G[y].push_back(make_pair(x, z));
        //scanf("%d", &d[x][y]);
    }
    memset(d, oo, sizeof(d));
    scanf("%d", &X);
    for(int i = 1 ; i <= N ; ++ i)
        Could[i] = BellmanFord(i);
    for(int i = 1 ; i <= N ; ++ i)
        if(Could[i])
            for(int j = 1 ; j <= N ; ++ j)
                dp[i] = max(dp[i], d[i][j]);
    if(Could[X])
        printf("%d\n", dp[X]);
        else printf("0\n");
    int Ans = oo, ind = 0;
    for(int i = 1 ; i <= N ; ++ i)
        if(Ans > dp[i] && dp[i])
            Ans = dp[i], ind = i;
    if(Ans == oo) {
        printf("0\n");
    }
    else
        printf("%d %d", ind, Ans);
    return 0;
}
