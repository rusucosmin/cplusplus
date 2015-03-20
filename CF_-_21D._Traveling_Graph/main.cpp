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

const int MAXN = 19;
const int oo = 0x3f3f3f3f;

typedef vector<pair<int, int> > Graph[MAXN];
typedef vector<pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int dp[1 << MAXN][MAXN], N, M;
Graph G;

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        cin >> x >> y >> z;
        if(x == y)
            continue;
        -- x; -- y;
        G[x].push_back(make_pair(y, z));
        G[y].push_back(make_pair(x, z));
    }
    memset(dp, oo, sizeof(dp));
    dp[1][0] = 0;
    for(int conf = 1 ; conf < (1 << N) ; ++ conf)
        for(int i = 0 ; i < N ; ++ i)
            if(conf & (1 << i))
                for(It it = G[i].begin(), fin = G[i].end(); it != fin ; ++ it)
                    if(conf & (1 << (it->first)))
                        dp[conf][i] = min(dp[conf][i], dp[conf ^ (1 << i)][it->first] + it->second);
    int Ans = oo;
    for(It it = G[0].begin(), fin = G[0].end(); it != fin ; ++ it)
        Ans = min(Ans, dp[(1 << N) - 1][it->first] + it->second);
    cout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
