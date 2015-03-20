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

const char infile[] = "orient.in";
const char outfile[] = "orient.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1005;
const int oo = 0x3f3f3f3f;

typedef vector<pair<int, int> > Graph[MAXN];
typedef vector<pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int Ans = oo;
Graph G;
int N, M, dp[MAXN], cmp;
int comp[MAXN];

inline int Dijkstra(int stNode, int fnNode) {
    priority_queue <pair<int, int> , vector <pair<int, int> > , greater <pair<int, int> > > Q;
    memset(dp, oo, sizeof(dp));
    dp[stNode] = 0;
    Q.push(make_pair(0, stNode));
    while(!Q.empty()) {
        int Node = Q.top().second;
        int cost = Q.top().first;
        Q.pop();
        if(dp[Node] < cost)
            continue;
        if(Node == fnNode)
            return cost;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
            if(dp[it->first] > cost + it->second && (Node != stNode || it->first != fnNode)) {
                dp[it->first] = cost + it->second;
                Q.push(make_pair(dp[it->first], it->first));
            }
        }
    }
    return oo;
}

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        fin >> x >> y >> z;
        G[x].push_back(make_pair(y, 0));
        G[y].push_back(make_pair(x, z));
    }
    fin.close();
    fin.open(infile);
    fin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        fin >> x >> y >> z;
        int aux = Dijkstra(x, y);
        int aux2 = Dijkstra(y, x);
        Ans = min(Ans, min(aux + z, aux2));
    }
    if(Ans == oo)
        Ans = 0;
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
