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
#include <cassert>

using namespace std;

const char infile[] = "obiective.in";
const char outfile[] = "obiective.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 32005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector< pair<int, bool> > WeightedGraph[MAXN];
typedef vector<int> :: iterator It;
typedef vector<pair<int, bool> > :: iterator wIt;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G, Gt;
WeightedGraph dag;
int N, M, Q, dp[MAXN], where[MAXN];
bitset <MAXN> Used;
vector <int> tsort;

inline void DFsPlus(const int &Node) {
    Used[Node] = true;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!Used[*it])
            DFsPlus(*it);
    tsort.push_back(Node);
}

inline void DFsMinus(const int &Node, const int &actCtc) {
    where[Node] = actCtc;
    for(It it = Gt[Node].begin(), fin = Gt[Node].end(); it != fin ; ++ it)
        if(!Used[*it])
            DFsMinus(*it, actCtc);
}

inline int Dijkstra(const int &stNode, const int &fnNode) {
    memset(dp, oo, sizeof(dp));
    priority_queue < pair<int, int> , vector <pair<int, int> > , greater < pair<int, int> > > Q;
    Q.push(make_pair(0, stNode));
    dp[stNode] = 0;
    while(!Q.empty()) {
        int Node = Q.top().second;
        int cost = Q.top().first;
        Q.pop();
        if(dp[Node] < cost)
            continue;
        if(Node == fnNode)
            return cost;
        for(wIt it = dag[Node].begin(), fin = dag[Node].end(); it != fin ; ++ it)
            if(dp[it->first] > cost + it->second) {
                dp[it->first] = cost + it->second;
                Q.push(make_pair(dp[it->first], it->first));
            }
    }
    assert(false);
}

int main() {
    int ctc = 0;
    fin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
        Gt[y].push_back(x);
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(!Used[i])
            DFsPlus(i);
    for(vector <int> :: reverse_iterator it = tsort.rbegin(), fin = tsort.rend(); it != fin ; ++ it)
        if(!where[*it])
            DFsMinus(*it, ++ctc);
    /// now we have to build the dag
    for(int i = 1 ; i <= N ; ++ i)
        for(It it = G[i].begin(), fin = G[i].end(); it != fin ; ++ it)
            if(where[i] != where[*it]) {
                dag[where[i]].push_back(make_pair(where[*it], 0));
                dag[where[*it]].push_back(make_pair(where[i], 1));
            }
    int T;
    for(fin >> T ; T -- ; ) {
        int A, B;
        fin >> A >> B;
        fout << Dijkstra(where[A], where[B]) << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
