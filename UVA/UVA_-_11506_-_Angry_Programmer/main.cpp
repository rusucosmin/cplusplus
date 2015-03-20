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

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, C[MAXN][MAXN], Father[MAXN];
int Source, Sink;
bitset <MAXN> Used;
queue <int> Q;
Graph G;

inline int in(int x) {
    return x;
}

inline int out(int x) {
    return x + N;
}

inline bool BFs(int Source, int Sink) {
    Used.reset();
    Q.push(Source);
    Used[Source] = 1;
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

inline int getMaxFlow(Graph &G, int Source, int Sink) {
    int maxFlow = 0;
    while(BFs(Source, Sink))
    for(It it = G[Sink].begin(), fin = G[Sink].end(); it != fin ; ++ it) {
        if(!Used[*it] || C[*it][Sink] <= 0)
            continue;
        Father[Sink] = *it;
        int bottleNeck = oo;
        for(int i = Sink ; i != Source ; i = Father[i])
            bottleNeck = min(bottleNeck, C[Father[i]][i]);
        for(int i = Sink ; i != Source ; i = Father[i]) {
            C[Father[i]][i] -= bottleNeck;
            C[i][Father[i]] += bottleNeck;
        }
        maxFlow += bottleNeck;
    }
    return maxFlow;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    while(cin >> N >> M) {
        if(!N && !M)
            return 0;
        Source = 0;
        Sink = 2 * N + 1;
        for(int i = 2 ; i < N ; ++ i) {
            int x, cost;
            cin >> x >> cost;
            G[in(x)].push_back(out(x));
            G[out(x)].push_back(in(x));
            C[in(x)][out(x)] = cost;
        }
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y, z;
            cin >> x >> y >> z;
            G[out(x)].push_back(in(y));
            G[in(y)].push_back(out(x));
            G[out(y)].push_back(in(x));
            G[in(x)].push_back(out(y));
            C[out(x)][in(y)] = z;
            C[out(y)][in(x)] = z;
        }
        //G[Source].push_back(out(1));
        //G[out(1)].push_back(Source);
        //C[Source][out(1)] = oo;
        //G[in(N)].push_back(Sink);
        //G[Sink].push_back(in(N));
        //C[in(N)][Sink] = oo;
        cout << getMaxFlow(G, out(1), in(N)) << '\n';
        for(int i = Source ; i <= Sink ; ++ i)
            vector <int> ().swap(G[i]);
        memset(C, 0, sizeof(C));
    }
    return 0;
}
