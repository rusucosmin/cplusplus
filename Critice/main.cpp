/**
 *  Muchiile critice sunt muchiile saturate care sunt accesibile din sursa si din destinatie doar pe muchii nesaturate ;)
 *
 */
#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <cmath>
#include <stdlib.h>
using namespace std;

ifstream cin("critice.in");
ofstream cout("critice.out");

const int MAXN = 1002;
const int MAXM = 10002;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

short N, M, Father[MAXN], C[MAXN][MAXN], F[MAXN][MAXN];
Graph G;
vector<pair<short, short> > Edge;
queue <short> Q, Critics;
bitset <MAXN> Vis, Source, Sink;

inline bool BFs() {
    int Node = 1;
    Vis.reset();
    for(Q.push(Node), Vis[Node] = true ; !Q.empty() ; Q.pop(), Node = Q.front())
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(!Vis[*it] && C[Node][*it] > F[Node][*it])
                Vis[*it] = true, Q.push(*it), Father[*it] = Node;
    return Vis[N];
}

inline void BFs(int Node, bitset <MAXN> & Viz) {
    for(Q.push(Node), Viz[Node] = true ; !Q.empty() ; Q.pop(), Node = Q.front())
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(!Viz[*it] && C[Node][*it] > abs(F[Node][*it]) )
                Viz[*it] = true, Q.push(*it), Father[*it] = Node;
}

inline void Read(short &N) {
    char s[20];
    cin >> s;
    N = atoi(s);
}

int main() {
    Read(N);
    Read(M);
    for(int i = 1 ; i <= M ; ++ i) {
        short x, y, z;
        Read(x);
        Read(y);
        Read(z);
        Edge.push_back(make_pair(x, y));
        G[x].push_back(y);
        G[y].push_back(x);
        C[x][y] = z;
        C[y][x] = z;
    }
    for( ; BFs() ; )
        for(int i = 0 ; i < G[N].size() ; ++ i) {
            int Node = G[N][i];
            if(C[Node][N] <= F[Node][N] || !Vis[N])
                continue;
            int minFlow = oo;
            Father[N] = Node;
            for(int i = N ; i != 1 ; i = Father[i])
                minFlow = min(minFlow, C[Father[i]][i] - F[Father[i]][i]);
            if(!minFlow)
                continue;
            for(int i = N ; i != 1 ; i = Father[i])
                F[Father[i]][i] += minFlow,
                F[i][Father[i]] -= minFlow;
        }
    BFs(1, Source);
    BFs(N, Sink);
    for(int i = 0 ; i < Edge.size() ; ++ i) {
        int x = Edge[i].first;
        int y = Edge[i].second;
        if((Source[x] && Sink[y]) || (Source[y] && Sink[x]))
            if(C[x][y] == F[x][y] || C[y][x] == F[y][x])
                Critics.push(i + 1);
    }
    for( cout << Critics.size() << '\n' ; !Critics.empty() ; Critics.pop() )
        cout << Critics.front() << '\n';
    cin.close();
    cout.close();
    return 0;
}
