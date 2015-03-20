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

typedef vector<int> Graph[2*MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, Father[2*MAXN], C[2*MAXN][2*MAXN];
int S, D, Source, Sink;
queue <int> Q;
bitset <2*MAXN> Used;
Graph G;

inline bool BFs(int Source, int Sink) {
    Q.push(Source);
    Used.reset();
    Used[Source] = 1;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        if(Node == Sink)
            continue;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(!Used[*it] && C[Node][*it] > 0) {
                Used[*it] = 1;
                Q.push(*it);
                Father[*it] = Node;
            }
    }
    return Used[Sink];
}

inline int getMaxFlow(Graph &G, int Source, int Sink) {
    int maxFlow = 0;
    while(BFs(Source, Sink)) {
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
            maxFlow += bottleNeck;
        }
    }
    return maxFlow;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    while(cin >> N) {
        Source = 0; Sink = 2*N + 1;
        for(int i = 1 ; i <= N ; ++ i) {
            int x;
            cin >> x;
            G[i].push_back(i + N);
            G[i + N].push_back(i);
            C[i][i + N] = x;
        }
        cin >> M;
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y, z;
            cin >> x >> y >> z;
            G[x + N].push_back(y);
            G[y].push_back(x + N);
            C[x + N][y] = z;
        }
        cin >> S >> D;
        for(int i = 1 ; i <= S ; ++ i) {
            int x;
            cin >> x;
            G[Source].push_back(x);
            G[x].push_back(Source);
            C[Source][x] = oo;
        }
        for(int i = 1 ; i <= D ; ++ i) {
            int x;
            cin >> x;
            C[x + N][Sink] = oo;
            G[x + N].push_back(Sink);
            G[Sink].push_back(x + N);
        }
        cout << getMaxFlow(G, Source, Sink) << '\n';
        memset(C, 0, sizeof(C));
        for(int i = Source ; i <= Sink ; ++ i)
            vector<int>().swap(G[i]);
    }
    return 0;
}
