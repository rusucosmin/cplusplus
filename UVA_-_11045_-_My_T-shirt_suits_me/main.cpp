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

const int MAXN = 70;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

map<string, int> _size;
int C[MAXN][MAXN], F[MAXN][MAXN], Father[MAXN], Source, Sink, N, M;
queue <int> Q;
bitset <MAXN> Used;
Graph G;

inline bool BFs(Graph &G, int Source, int Sink) {
    Q.push(Source);
    Used.reset();
    Used[Source] = 1;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        if(Node == Sink)
            continue;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(!Used[*it] && C[Node][*it] - F[Node][*it] > 0) {
                Used[*it] = 1;
                Father[*it] = Node;
                Q.push(*it);
            }
    }
    return Used[Sink];
}

inline int getMaximumMatching(Graph &G, int Source, int Sink) {
    int maxFlow = 0;
    while(BFs(G, Source, Sink)) {
        for(It it = G[Sink].begin(), fin = G[Sink].end(); it != fin ; ++ it) {
            if(!Used[*it] || C[*it][Sink] - F[*it][Sink] <= 0)
                continue;
            Father[Sink] = *it;
            int bottleNeck = oo;
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
    }
    return maxFlow;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    int T;
    cin >> T;
    _size["XXL"] = 1;
    _size["XL"] = 2;
    _size["L"] = 3;
    _size["M"] = 4;
    _size["S"] = 5;
    _size["XS"] = 6;
    for(int test = 1 ; test <= T ; ++ test) {
        cin >> M >> N;  /// the no of T-shirt and the no of people
        Source = 0;
        Sink = 6 + N + 1;
        for(int i = 1 ; i <= N ; ++ i) {
            string a, b;
            cin >> a >> b;
            int x = i;
            int y = _size[a];
            G[x].push_back(y + N);
            G[y + N].push_back(x);
            C[x][y + N] = 1;
            y = _size[b];
            G[x].push_back(y + N);
            G[y + N].push_back(x);
            C[x][y + N] = 1;

            G[Source].push_back(x);
            G[x].push_back(Source);

            C[Source][x] = 1;
        }
        for(int i = 1 ; i <= 6 ; ++ i) {
            G[i + N].push_back(Sink);
            G[Sink].push_back(i + N);
            C[i + N][Sink] = M / 6;
        }
        int maxFlow = getMaximumMatching(G, Source, Sink);
        if(maxFlow == N)
            cout << "YES\n";
        else cout << "NO\n";
        memset(C, 0, sizeof(C));
        memset(F, 0, sizeof(F));
        for(int i = Source ; i <= Sink ; ++ i)
            vector <int>().swap(G[i]);
    }
    fin.close();
    fout.close();
    return 0;
}
