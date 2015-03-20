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

const char infile[] = "ubuntzei.in";
const char outfile[] = "ubuntzei.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXK = 18;
const int MAXN = 2005;
const int oo = 0x3f3f3f3f;

typedef vector<pair<int, int> > Graph[MAXN];
typedef vector<pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;
int N, M, K, U[MAXK];
int dist[MAXK][MAXK], d[MAXN];
int dp[1 << MAXK][MAXK];

inline void Dijkstra(const int &stNode) {
    priority_queue <pair<int, int>, vector <pair<int, int> >, greater <pair<int, int> > > Q;
    memset(d, oo, sizeof(d));
    d[stNode] = 0;
    Q.push(make_pair(0, stNode));
    while(!Q.empty()) {
        int cost = Q.top().first;
        int Node = Q.top().second;
        Q.pop();
        if(cost > d[Node])
            continue;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(d[it->first] > cost + it->second) {
                d[it->first] = cost + it->second;
                Q.push(make_pair(d[it->first], it->first));
            }
    }
}

int main() {
    fin >> N >> M >> K;
    U[0] = 1;
    for(int i = 1 ; i <= K ; ++ i)
        fin >> U[i];
    U[++ K] = N;
    ++ K;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        fin >> x >> y >> z;
        G[x].push_back(make_pair(y, z));
        G[y].push_back(make_pair(x, z));
    }
    for(int i = 0 ; i < K ; ++ i) {
        Dijkstra(U[i]);
        for(int j = 0 ; j < K ; ++ j)
            dist[i][j] = d[U[j]];
        dist[i][i] = 0;
    }
    memset(dp, oo, sizeof(dp));
    dp[1][0] = 0;
    const int maxConf = (1 << K);
    for(int conf = 1 ; conf < maxConf ; ++ conf)
        for(int i = 0 ; i < K ; ++ i)
            if(conf & (1 << i))
                for(int j = 0 ; j < K ; ++ j)
                    if(conf & (1 << j))
                        dp[conf][i] = min(dp[conf][i], dp[conf ^ (1 << i)][j] + dist[j][i]);
    fout << dp[maxConf - 1][K - 1] << '\n';
    fin.close();
    fout.close();
    return 0;
}
