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

const int MAXN = 250;
const int oo = 0x3f3f3f3f;

typedef vector< pair<int, int> > Graph[MAXN];
typedef vector< pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, C, K;
Graph G;
int d[MAXN][MAXN], dist[MAXN];
int dp[MAXN];

#define fin cin
#define fout cout

inline int BFs(const int &stNode) {
    dp[stNode] = 0;
    queue <int> Q;
    Q.push(stNode);
    int Ans = oo;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        if(Node < C - 1) {
            dp[C - 1] = min(dp[C - 1], dp[Node] + dist[Node]);
            continue;
        }
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
            if(dp[it->first] > dp[Node] + it->second) {
                dp[it->first] = dp[Node] + it->second;
                Q.push(it->first);
            }
        }
    }
    Ans = min(Ans, dp[C - 1]);
    return Ans;
}

int main() {
    cin.sync_with_stdio(false);
    while(true) {
        memset(d, 0, sizeof(d));
        memset(dist, 0, sizeof(dist));
        memset(dp, oo, sizeof(dp));
        for(int i = 1 ; i <= N ; ++ i)
         vector <pair<int, int> > ().swap(G[i]);
        fin >> N >> M >> C >> K;
        if(!N && !M && !C && !K)
            return 0;
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y, z;
            fin >> x >> y >> z;
            G[x].push_back(make_pair(y, z));
            G[y].push_back(make_pair(x, z));
            d[x][y] = z;
            d[y][x] = z;
        }
        dist[C - 1] = 0;
        for(int i = C - 2 ; i >= 0 ; -- i)
            dist[i] = dist[i + 1] + d[i][i + 1];
        fout << BFs(K) << '\n';
    }
    return 0;
}
