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

const int MAXN = 205;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int C[MAXN][MAXN], F[MAXN][MAXN];
int Father[MAXN];
int N, T;
Graph G;
queue <int> Q;
bitset <MAXN> Used;

inline bool BFs(int Source, int Sink) {
    Used.reset();
    Q.push(Source);
    Used[Source] = 1;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        if(Node == Sink)
            continue;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
            if(!Used[*it] && C[Node][*it] - F[Node][*it] > 0) {
                Used[*it] = true;
                Father[*it] = Node;
                Q.push(*it);
            }
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
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    for(cin >> T ; T ; -- T) {
        cin >> N;
        for(int i = 1 ; i < N ; ++ i) {
            int nr, x;
            cin >> nr;
            for(int j = 1 ; j <= nr ; ++ j) {
                cin >> x;
                G[i].push_back(x);
                G[x].push_back(i);
                C[i][x] = oo;
                if(i == 1 || x == N)
                    C[i][x] = 1;
            }
        }
        cout << getMaxFlow(G, 1, N) << '\n';
        memset(C, 0, sizeof(C));
        memset(F, 0, sizeof(F));
        for(int i = 1 ; i <= N ; ++ i)
            vector <int>().swap(G[i]);
    }
    fin.close();
    fout.close();
    return 0;
}
