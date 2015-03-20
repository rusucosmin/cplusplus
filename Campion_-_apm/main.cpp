#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <queue>
#include <string.h>
#include <algorithm>

using namespace std;

const char infile[] = "apm.in";
const char outfile[] = "apm.out";

const int MAXN = 260;
const int oo = 0x3f3f3f3f;

typedef vector< pair<int, int> > Graph[MAXN];
typedef vector< pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N;
int best[MAXN];
int d[MAXN][MAXN];
vector < pair<int, pair<int, int> > > v;
bitset <MAXN> used[MAXN], gr[MAXN];
Graph G;

inline void BFs(const int &startNode) {
    queue <int> Q;
    memset(best, oo, sizeof(best));
    for(Q.push(startNode), best[startNode] = 0 ; !Q.empty() ; Q.pop()) {
        int Node = Q.front();
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(best[it->first] > best[Node] + it->second) {
                best[it->first] = best[Node] + it->second;
                Q.push(it->first);
            }
    }
}

int main() {
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    scanf("%d", &N);
    for(int i = 1 ; i != N ; ++ i) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        gr[x][y] = 1;
        gr[y][x] = 1;
        G[x].push_back(make_pair(y, z));
        G[y].push_back(make_pair(x, z));
    }
    int M;
    scanf("%d", &M);
    for(int i = 1 ; i <= M ; ++ i) {
        int x;
        scanf("%d", &x);
        v.push_back(make_pair(x, make_pair(-1, -1)));
    }
    for(int i = 1 ; i <= N ; ++ i) {
        BFs(i);
        for(int j = 1 ; j <= N ; ++ j)
            d[i][j] = best[j], v.push_back(make_pair(d[i][j], make_pair(i, j)));
    }
    sort(v.begin(), v.end());
    bool ok = true;
    int i = 0;
    while(v[i].second != make_pair(-1, -1) && i < v.size())
        ++ i;
    int last = v[i-1].first;
    for( int n = v.size() ; i < n ;) {
        while(v[i].second == make_pair(-1, -1) && i < n)
            ++ i;
        if(i >= n)
            break;
        int x = v[i].second.second;
        int y = v[i].second.first;
        cout << v[i].second.first << ' ' << v[i].second.second << ' ' << last << '\n';
        ++ i;
        while(v[i].second != make_pair(-1, -1) && i < n)
            ++ i;
        last = v[i-1].first;
    }
    return 0;
}
