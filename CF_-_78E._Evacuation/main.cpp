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

const int MAXN = 15;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN * MAXN * 2];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1,  0,-1};

int N, T;
char a[MAXN][MAXN], b[MAXN][MAXN];
int getInfected[MAXN][MAXN];
int dp[MAXN][MAXN][MAXN][MAXN], Nodes;
int C[MAXN * MAXN * 2][MAXN * MAXN * 2];
int Source, Sink;
queue <pair<int, int> > Q;
Graph G;
int Father[MAXN * MAXN * 2];
bitset <MAXN * MAXN> Used;

inline bool inside(int x, int y) {
    return x >= 1 && x <= N && y >= 1 && y <= N;
}

inline int getNode(int x, int y) {
    return (x - 1) * N + y;
}

inline void buildInfectedTime() {
    memset(getInfected, oo, sizeof(getInfected));
    getInfected[Q.front().first][Q.front().second] = 0;
    while(!Q.empty()) {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();
        for(int d = 0 ; d < 4 ; ++ d) {
            int xnou = x + dx[d];
            int ynou = y + dy[d];
            if(inside(xnou, ynou) && getInfected[xnou][ynou] == oo & a[xnou][ynou] != 'Y') {
                getInfected[xnou][ynou] = getInfected[x][y] + 1;
                Q.push(make_pair(xnou, ynou));
            }
        }
    }
}

inline void BFs(int xst, int yst) {
    Q.push(make_pair(xst, yst));
    dp[xst][yst][xst][yst] = 0;
    while(!Q.empty()) {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();
        for(int d = 0 ; d < 4 ; ++ d) {
            int xnou = x + dx[d];
            int ynou = y + dy[d];
            if(inside(xnou, ynou) && dp[xst][yst][xnou][ynou] == oo && isdigit(a[xnou][ynou]) &&  (getInfected[xnou][ynou] > dp[xst][yst][x][y])) {
                if(getInfected[xnou][ynou] > dp[xst][yst][x][y] + 1)
                    Q.push(make_pair(xnou, ynou)); /// but why ? :))
                dp[xst][yst][xnou][ynou] = dp[xst][yst][x][y] + 1;
            }
        }
    }
}

inline bool BFs(Graph &G, int Source, int Sink) {
    queue <int> Q;
    Used.reset();
    Q.push(Source);
    Used[Source] = 1;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        if(Node == Sink)
            continue;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(!Used[*it] && C[Node][*it] > 0) {
                Used[*it] = 1;
                Father[*it] = Node;
                Q.push(*it);
            }
    }
    return Used[Sink];
}

inline int getMaxFlow(Graph &G, int Source, int Sink) {
    int maxFlow = 0;
    while(BFs(G, Source, Sink))
        for(It it = G[Sink].begin(), fin = G[Sink].end(); it != fin ; ++ it) {
            if(!Used[*it] || C[*it][Sink] <= 0)
                continue;
            int bottleNeck = oo;
            Father[Sink] = *it;
            for(int i = Sink ; i != Source ; i = Father[i])
                bottleNeck = min(bottleNeck, C[Father[i]][i]);
            if(!bottleNeck)
                continue;
            for(int i = Sink ; i != Source ; i = Father[i]) {
                C[Father[i]][i] -= bottleNeck;
                C[i][Father[i]] += bottleNeck;
            }
            maxFlow += bottleNeck;
        }
    return maxFlow;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> N >> T;
    for(int i = 1 ; i <= N ; ++ i)
        cin >> (a[i] + 1);
    for(int i = 1 ; i <= N ; ++ i)
        cin >> (b[i] + 1);
    for(int i = 1 ; i <= N && Q.empty() ; ++ i)
        for(int j = 1 ; j <= N && Q.empty() ; ++ j)
            if(a[i][j] == 'Z')
                Q.push(make_pair(i, j));
    buildInfectedTime();
    Source = 0;
    Sink = N * N + getNode(N, N + 1);
    memset(dp, oo, sizeof(dp));
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= N ; ++ j) {
            if(isdigit(a[i][j]) && a[i][j] > '0') {
                BFs(i, j);
                for(int x = 1 ; x <= N ; ++ x)
                    for(int y = 1 ; y <= N ; ++ y)
                        if(dp[i][j][x][y] <= T && isdigit(b[x][y]) && b[x][y] > '0') {
                            G[getNode(i, j)].push_back(N * N + getNode(x, y));
                            G[N * N + getNode(x, y)].push_back(getNode(i, j));
                            C[getNode(i, j)][N * N + getNode(x, y)] = oo;
                        }
                G[Source].push_back(getNode(i, j));
                G[getNode(i, j)].push_back(Source);
                C[Source][getNode(i, j)] = a[i][j] - '0';
            }
            if(isdigit(b[i][j]) && b[i][j] > '0') {
                G[N * N + getNode(i, j)].push_back(Sink);
                G[Sink].push_back(N * N + getNode(i, j));
                C[N * N + getNode(i, j)][Sink] = b[i][j] - '0';
            }
        }
    int ans = getMaxFlow(G, Source, Sink);
    cout << ans << '\n';
    return 0;
}
