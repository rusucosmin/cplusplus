#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <string.h>
#include <stdlib.h>

using namespace std;

const char infile[] = "algola.in";
const char outfile[] = "algola.out";

ifstream f(infile);
ofstream g(outfile);

const int MAXN = 5010;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, P[MAXN], totalP, Source, Sink, C[MAXN][MAXN], T, Father[MAXN], F[MAXN][MAXN], maxFlow;
Graph G;
vector<pair<int, int> > W[MAXN];
queue <int> Q;
bitset <MAXN> used;

inline bool BFs() {
    memset(Father, 0, sizeof(Father));
    used.reset();
    for(Q.push(Source), used[Source] = 1 ; !Q.empty() ; Q.pop()) {
        int Node = Q.front();
        if(Node == Sink)    continue;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(!used[*it] && C[Node][*it] - F[Node][*it] > 0) {
                used[*it] = true;
                Father[*it] = Node;
                Q.push(*it);
            }
    }
    return used[Sink];
}

void actMaxFlow() {
    for( ; BFs() ; )
        for(It it = G[Sink].begin(), fin = G[Sink].end(); it != fin ; ++ it) {
            if(!used[*it] || C[*it][Sink] - F[*it][Sink] <= 0)
                continue;
            int minFlow = oo;
            for(int i = Sink ; i != Source && minFlow ; i = Father[i])
                minFlow = min(minFlow, C[Father[i]][i] - F[Father[i]][i]);
            if(!minFlow)    continue;
            for(int i = Sink ; i != Source ; i = Father[i]) {
                F[Father[i]][i] += minFlow;
                F[i][Father[i]] -= minFlow;
            }
            maxFlow += minFlow;
        }
}

inline void AddEdges(const int &T) {
    for(int i = 1 ; i <= N ; ++ i) {
        int x = (T - 1) * N + i;
        G[x].push_back(x + N);
        G[x + N].push_back(x);
        C[x][x+N] = oo;
        for(vector<pair<int, int> > :: iterator it = W[i].begin(), fin = W[i].end() ; it != fin ; ++ it) {
            int y = N * T + it->first;
            G[x].push_back(y);
            G[y].push_back(x);
            C[x][y] = it->second;
        }
    }
}

inline void Solve() {
    for(int T = 1 ; ; ++ T) {
        AddEdges(T);
        Sink = N * T + 1;
        actMaxFlow();
        if(maxFlow == totalP) {
            g << T << '\n';
            exit(0);
        }
    }
}

int main() {
    f >> N >> M;
    Source = 0;
    Sink = N + 1;
    for(int i = 1 ; i <= N ; ++ i) {
        f >> P[i];
        totalP += P[i];

        G[Source].push_back(i);
        G[i].push_back(Source);

        C[Source][i] = P[i];
    }
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        f >> x >> y >> z;

        W[x].push_back(make_pair(y, z));
        W[y].push_back(make_pair(x, z));
    }
    Solve();
    f.close();
    g.close();
    return 0;
}
