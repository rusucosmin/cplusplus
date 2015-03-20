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

const char infile[] = "siret.in";
const char outfile[] = "siret.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 305;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, dp[MAXN], Father[MAXN];
bool a[MAXN][MAXN];
Graph G;
int tsort[MAXN];
bitset <MAXN> Used;

void DFs(int Node) {
    Used[Node] = true;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!Used[*it])
            DFs(*it);
    tsort[++ tsort[0] ] = Node;
}

void Write(int Node) {
    fout << tsort[Node] << ' ';
    if(Father[Node])
        Write(Father[Node]);
}

inline void buildLongestIncreasingSubsequence() {
    int Ans = 0;
    for(int i = 1 ; i <= N ; ++ i) {
        dp[i] = 1;
        for(int j = 1 ; j < i ; ++ j)
            if(tsort[i] < tsort[j] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
                if(dp[Ans] < dp[i])
                    Ans = i;
                Father[i] = j;
            }
    }
    fout << dp[Ans] << '\n';
    Write(Ans);
}

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        fin >> x >> y;
        a[x][y] = 1;
        a[y][x] = 1;
    }
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = i + 1 ; j <= N ; ++ j)
            if(a[i][j])
                G[j].push_back(i);
                else G[i].push_back(j);
    for(int i = 1 ; i <= N ; ++ i)
        if(!Used[i])
            DFs(i);
    reverse(tsort + 1, tsort + N + 1);
    buildLongestIncreasingSubsequence();
    fin.close();
    fout.close();
    return 0;
}
