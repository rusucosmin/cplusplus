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
const int oo = 0x3f3f3f3f;

typedef vector<pair<int, int> > Graph[MAXN];
typedef vector<pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int T, N, M, S, D, K;
int dp[MAXN], dpT[MAXN];
Graph G, Gt;

inline void Dijkstra(Graph E, int d[MAXN], int stNode) {
    priority_queue <pair<int, int> , vector <pair<int, int> > , greater <pair<int, int> > > Q;
    d[stNode] = 0;
    Q.push(make_pair(0, stNode));
    while(!Q.empty()) {
        int Node = Q.top().second;
        int cost = Q.top().first;
        Q.pop();
        if(d[Node] < cost)
            continue;
        for(It it = E[Node].begin(), fin = E[Node].end(); it != fin ; ++ it)
            if(d[it->first] > cost + it->second) {
                d[it->first] = cost + it->second;
                Q.push(make_pair(d[it->first], it->first));
            }
    }
}

int main() {
    scanf("%d", &T);
    for(int test = 1  ; test <= T ; ++ test) {
        scanf("%d%d%d%d%d", &N, &M, &K, &S, &D);
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            G[x].push_back(make_pair(y, z));
            Gt[y].push_back(make_pair(x, z));
        }
        memset(dp, oo, sizeof(dp));
        memset(dpT, oo, sizeof(dpT));
        Dijkstra(G, dp, S);
        Dijkstra(Gt, dpT, D);
        int Ans = dp[D];
        for(int i = 1 ; i <= K ; ++ i) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            Ans = min(Ans, dp[x] + dpT[y] + z);
            Ans = min(Ans, dpT[x] + dp[y] + z);
        }
        if(Ans == oo)
            Ans = -1;
        printf("%d\n", Ans);
        for(int i = 1 ; i <= N ; ++ i) {
            vector <pair<int, int> > ().swap(G[i]);
            vector <pair<int, int> > ().swap(Gt[i]);
        }
    }
    return 0;
}
