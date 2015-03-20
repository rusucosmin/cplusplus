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

const int MAXN = 100;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int C[MAXN][MAXN];
int N, M, Father[MAXN], Source, Sink;
vector <pair<int, int> > Edges;
bitset <MAXN> Used;
queue <int> Q;
Graph G;

inline bool BFs(int Source, int Sink) {
    Used.reset();
    Q.push(Source);
    Used[Source] = true;
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

inline void getMaxFlow(Graph &G, int Source, int Sink) {
    while(BFs(Source, Sink))
        for(It it = G[Sink].begin(), fin = G[Sink].end(); it != fin ; ++ it) {
            if(!Used[*it] || C[*it][Sink] <= 0)
                continue;
            Father[Sink] = *it;
            int bottleNeck = oo;
            for(int i = Sink ; i != Source ; i = Father[i])
                bottleNeck = min(bottleNeck, C[Father[i]][i]);
            if(!bottleNeck)
                continue;
            for(int i = Sink ; i != Source ; i = Father[i]) {
                C[Father[i]][i] -= bottleNeck;
                C[i][Father[i]] += bottleNeck;
            }
        }
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    while(scanf("%d%d", &N, &M) == 2) {
        if(!N && !M)
            return 0;
        int x, y, z;
        for(int i = 1 ; i <= M ; ++ i) {
            scanf("%d%d%d", &x, &y, &z);
            Edges.push_back(make_pair(x, y));
            G[x].push_back(y);
            G[y].push_back(x);
            C[x][y] = z;
            C[y][x] = z;
        }
        getMaxFlow(G, 1, 2);
        for(vector <pair<int, int> > :: iterator it = Edges.begin(), fin = Edges.end(); it != fin ; ++ it)
            if(Used[it->first] + Used[it->second] == 1) {
                printf("%d %d\n", it->first, it->second);
                C[it->first][it->second] = 0;
                C[it->second][it->first] = 0;
            }
        vector <pair<int, int> > ().swap(Edges);
        printf("\n");
        for(int i = 1 ; i <= N ; ++ i)
            vector <int>().swap(G[i]);
    }
    return 0;
}
