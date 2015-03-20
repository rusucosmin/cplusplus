#include <stdio.h>
#include <vector>
#include <bitset>
#include <queue>
#include <limits.h>

using namespace std;

const char infile[] = "kimberley.in";
const char outfile[] = "kimberley.out";

const int MAXN = 55 * 10;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

int N, G, S, D, M, maxFlow, Father[MAXN];
int C[MAXN][MAXN];
bitset <55> Gr[55];
bitset <MAXN> E[MAXN];
bitset <MAXN> Used;
queue <int> Q;

inline void buildNetwork(const int &T) {
    for(int i = 1 ; i <= N ; ++ i) {
        int x = i + N * ( T - 1 );
        E[x][x+N] = 1;
        C[x][x+N] = CHAR_MAX;
        E[x+N][x] = 1;
        for(int it = 1 ; it <= N ; ++ it)
            if(Gr[i][it]) {
                int y = it + (N * T);
                E[x][y] = 1;
                E[y][x] = 1;
                C[x][y] = 1;
            }
    }
}

inline bool BFs(const int &startNode) {
    Used.reset();
    Q.push(startNode);
    Used[startNode] = true;
    while( !Q.empty() ) {
        int Node = Q.front();
        Q.pop();
        if(Node == D)
            continue;
        for(int it = 1 ; it <= D ; ++ it)
            if(E[Node][it] && !Used[it] && C[Node][it] > 0) {
                Father[it] = Node;
                Used[it] = true;
                Q.push(it);
            }
    }
    return Used[D];
}

inline void buildMaxFlow() {
    while( BFs(S) ) {
        //for(int it = 1 ; it <=  ; ++ it) {
        //    if(!Used[it] || C[it][D] <= 0)
        //        continue;
        //    Father[D] = it;
            int minFlow = CHAR_MAX;
            for(int i = D ; i != S ; i = Father[i])
                minFlow = min(minFlow, (int)C[Father[i]][i]);
            if(!minFlow)
                continue;
            for(int i = D ; i != S ; i = Father[i]) {
                //printf("%d ", i);
                C[Father[i]][i] -= minFlow;
                C[i][Father[i]] += minFlow;
            }
            //printf("\n");
            maxFlow += minFlow;
    }
        //}
}

int main() {
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    scanf("%d %d", &N, &G); /// N - nr de noduri G - nr de muchii
    scanf("%d %d %d", &S, &D, &M); /// S - sursa, D - destinatia M - nr de mineri
    for(int i = 1 ; i <= G ; ++ i) {
        int x, y;
        scanf("%d %d", &x, &y);
        Gr[x][y] = 1;
        Gr[y][x] = 1;
    }
    for(int t = 1 ; t <= N + M ; ++ t) {
        D += N;
        buildNetwork(t);
        buildMaxFlow();
        if(maxFlow >= M) {
            printf("%d\n", t);
            return 0;
        }
    }
    return 0;
}
