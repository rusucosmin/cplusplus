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

const int MAXN = 105;
const int oo = 0x3f3f3f3f;

typedef vector<pair<int, int> > Graph[MAXN];
typedef vector<pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int T, N, M, Q, Father[MAXN], dp[MAXN];
Graph G;
bitset <MAXN> Used;

inline void BFs(int Source, int Sink) {
    queue <int> Q;
    Used.reset();
    memset(dp, -1, sizeof(dp));
    Used[Source] = 1;
    Q.push(Source);
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        if(Node == Sink)
            return ;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(!Used[it->first]) {
                dp[it->first] = max(dp[Node], it->second);
                Used[it->first] = 1;
                Q.push(it->first);
            }
    }
}

inline int Find(int Node) {
    if(Father[Node] != Node)
        Father[Node] = Find(Father[Node]);
    return Father[Node];
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    int test = 0;
    while(scanf("%d %d %d", &N, &M, &Q) == 3) {
        if(!N && !M && !Q)
            return 0;
        if(test)
            printf("\n");
        vector <pair<int, pair<int, int> > > Edges;
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            Edges.push_back(make_pair(z, make_pair(x, y)));
        }
        for(int i = 1 ; i <= N ; ++ i) {
            Father[i] = i;
            vector <pair<int, int> > ().swap(G[i]);
        }
        sort(Edges.begin(), Edges.end());
        for(vector <pair<int, pair<int, int> > > :: iterator it = Edges.begin(), fin = Edges.end(); it != fin ; ++ it) {
            int x = Find(it->second.first);
            int y = Find(it->second.second);
            if(x != y) {
                Father[x] = y;
                G[it->second.first].push_back(make_pair(it->second.second, it->first));
                G[it->second.second].push_back(make_pair(it->second.first, it->first));
            }
        }
        printf("Case #%d\n", ++ test);
        for(int i = 1 ; i <= Q ; ++ i) {
            int x, y;
            scanf("%d %d", &x, &y);
            BFs(x, y);
            if(dp[y] == -1)
                printf("no path\n");
            else
                printf("%d\n", dp[y]);
        }
    }
    return 0;
}
