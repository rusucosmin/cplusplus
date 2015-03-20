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
const int MAXK = 1005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, K, v[MAXN], vmax[MAXN];
int dp[MAXN][MAXK];
int tsort[MAXN];
Graph G;
bitset <MAXN> Used;

void DFs(const int &Node) {
    Used[Node] = true;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!Used[*it])
            DFs(*it);
    tsort[++ tsort[0]] = Node;
}

int main() {
    memset(vmax, -oo, sizeof(vmax));
    memset(dp, -oo, sizeof(dp));
    fin >> N >> M >> K;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> v[i];
        dp[i][0] = v[i];
    }
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
    }
    for(int i = 1 ; i <= N ; ++ i) {
        int x;
        fin >> x;
        for(int j = 1 ; j <= x ; ++ j) {
            int y;
            fin >> y;
            vmax[i] = max(vmax[i], v[y]);
        }
        dp[i][1] = vmax[i];
        //fout << i << ' ' << vmax[i] << '\n';
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(!Used[i])
            DFs(i);
    int Ans = 0;
    for(int i = 1 ; i <= tsort[0] ; ++ i) {
        int Node = tsort[i];
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
            dp[Node][0] = max(dp[Node][0], dp[*it][0] + v[*it]);
            Ans = max(Ans, dp[Node][0]);
            for(int j = 0 ; j <= K ; ++ j) {
                dp[Node][j] = max(dp[Node][j], dp[*it][j] + v[Node]);
                dp[Node][j] = max(dp[Node][j], dp[*it][j - 1] + vmax[Node]);
                Ans = max(Ans, dp[Node][j]);
            }
        }
    }
    /*
        for(int i = 1 ; i <= N ; ++ i, fout << '\n')
            for(int j = 1 ; j <= K ; ++ j)
                fout << dp[i][j] << ' ';
    */
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
