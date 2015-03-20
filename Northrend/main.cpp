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

const char infile[] = "northrend.in";
const char outfile[] = "northrend.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<pair<int, int> > Graph[MAXN];
typedef vector<pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct classComp {
    inline bool operator () (const pair<int, int> &a, const pair<int, int> &b ) const {
        return a.second < b.second;
    }
};

int ans, N, X;
Graph g;

inline void dfs(int node, int father) {
    for(auto it : g[node]) {
        if(father == it.first)
            continue;
        int y = it.first;
        int cost = it.second;
        if(g[y][0].second == cost) {
            dfs(y, node);
            ans += (g[y].size() - 1);
        }
        else if(g[y].size() > 1)
            if(g[y][1].second == cost) {
                ++ ans;
                dfs(g[y][1].second, y);
            }
    }
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    fin >> N >> X;
    for(int i = 1 ; i < N ; ++ i) {
        int x, y, z;
        fin >> x >> y >> z;
        g[x].push_back(make_pair(y, z));
        g[y].push_back(make_pair(x, z));
    }
    for(int i = 1 ; i <= N ; ++ i)
        sort(g[i].begin(), g[i].end(), classComp());
    dfs(X, 0);
    fout << ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
