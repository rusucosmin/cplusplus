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

int T, N, M, Source, Sink, C[MAXN][MAXN], Father[MAXN], F[MAXN][MAXN];
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
            if(!Used[*it] && C[Node][*it] - F[Node][*it] > 0) {
                Used[*it] = true;
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
            if(!Used[*it] || C[*it][Sink] - F[*it][Sink] <= 0)
                continue;
            int bottleNeck = oo;
            Father[Sink] = *it;
            for(int i = Sink ; i != Source ; i = Father[i])
                bottleNeck = min(bottleNeck, C[Father[i]][i] - F[Father[i]][i]);
            if(!bottleNeck)
                continue;
            for(int i = Sink ; i != Source ; i = Father[i]) {
                F[Father[i]][i] += bottleNeck;
                F[i][Father[i]] -= bottleNeck;
            }
            maxFlow += bottleNeck;
        }
    return maxFlow;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    scanf("%d", &T);
    for(int test = 1 ; test <= T ; ++ test) {
        scanf("%d%d", &N, &M);
        int j = 0;
        memset(C, 0, sizeof(C));
        for(int i = 0 ; i <= 2 * N ; ++ i)
            vector <int>().swap(G[i]);
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y;
            scanf(" (%d,%d)", &x, &y);
            ++ x;
            ++ y;
            G[x + N].push_back(y);
            G[y].push_back(x + N);

            G[y + N].push_back(x);
            G[x].push_back(y + N);
            if(!C[x + N][y])
                ++ j;
            C[x + N][y] = N + 1;
            C[y + N][x] = N + 1;
        }
        for(int i = 1 ; i <= N ; ++ i) {
            G[i].push_back(i + N);
            G[i + N].push_back(i);
            C[i][i + N] = 1;
        }
        if(j == 0) {
            if(N > 1)
                printf("%d\n", 0);
            else printf("%d\n", N);
            continue;
        }
        if (N == 0 || j >= (N * (N - 1) / 2)) {
			printf("%d\n", N);
			continue;
		}
        int Ans = oo;
        Source = 1 + N;
        for(Sink = Source - N + 1 ; Sink <= N ; ++ Sink) {
            memset(F, 0, sizeof(F));
            Ans = min(Ans, getMaxFlow(G, Source, Sink));
        }
        if(Ans == oo)
            Ans = 0;
        printf("%d\n", Ans);
    }
    return 0;
}
