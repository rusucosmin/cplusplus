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

const char infile[] = "hamilton.in";
const char outfile[] = "hamilton.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 18;
const int oo = 0x3f3f3f3f;

typedef vector<pair<int, int> > Graph[MAXN];
typedef vector<pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;
int dp[1 << MAXN][MAXN];
int N, M;

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int node1, node2, cost;
        fin >> node1 >> node2 >> cost;
        G[node2].push_back(make_pair(node1, cost));
    }
    memset(dp, oo, sizeof(dp));
    dp[1][0] = 0;
    const int maxConf = (1 << N);
    for(int i = 1 ; i < maxConf ; ++ i) {
        for(int j = 0 ; j < N ; ++ j)
            if(i & (1 << j))
                for(It it = G[j].begin(), fin = G[j].end(); it != fin ; ++ it)
                    if(i & (1 << it->first))
                        dp[i][j] = min(dp[i][j], dp[i ^ (1 << j)][it->first] + it->second);
    }
    int Ans = oo;
    for(It it = G[0].begin(), fin = G[0].end(); it != fin ; ++ it)
        Ans = min(Ans, dp[maxConf - 1][it->first] + it->second);
    if(Ans == oo) {
        fout << "Nu exista solutie\n";
        return 0;
    }
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
