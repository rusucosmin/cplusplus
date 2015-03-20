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

const int MAXN = 30025;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[2*MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;
int Father[2*MAXN];
map <pair<int, int> , int> C;
int T, N, M;
int First = 1, Second = 2, Third = 3;
int Source = 0, Sink;
bitset <2*MAXN> Used;
queue <int> Q;

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
            if(!Used[*it] && C[make_pair(Node, *it)]) {
                Used[*it] = true;
                Father[*it] = Node;
                Q.push(*it);
            }
    }
    return Used[Sink];
}

inline int getMaxFlow(Graph &G, int Source, int Sink) {
    int maxFlow = 0;
    while(BFs(Source, Sink)) {
        for(It it = G[Sink].begin(), fin = G[Sink].end(); it != fin ; ++ it) {
            if(!Used[*it] || !C[make_pair(*it, Sink)])
                continue;
            Father[Sink] = *it;
            int bottleNeck = oo;
            for(int i = Sink ; i != Source ; i = Father[i])
                bottleNeck = min(bottleNeck, C[make_pair(Father[i],i)]);
            if(!bottleNeck)
                continue;
            for(int i = Sink ; i != Source ; i = Father[i]) {
                C[make_pair(Father[i],i)] -= bottleNeck;
                C[make_pair(i, Father[i])] += bottleNeck;
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
    for(cin >> T ; T -- ; ) {
        cin >> N >> M;
        Sink = 2 * N + 1;
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y;
            cin >> x >> y;

            G[x + N].push_back(y);
            G[y].push_back(x + N);

            C[make_pair(x + N, y)] = 1;

            G[y + N].push_back(x);
            G[x].push_back(y + N);

            C[make_pair(y + N, x)] = 1;
        }
        for(int i = 1 ; i <= N ; ++ i) {
            G[i].push_back(i + N);
            C[make_pair(i, i + N)] = 1;
        }

        G[Source].push_back(First);
        G[First].push_back(Source);
        C[make_pair(Source, First)] = 1;

        G[Source].push_back(Third);
        G[Third].push_back(Source);
        C[make_pair(Source, Third)] = 1;

        G[2 + N].push_back(Sink);
        G[Sink].push_back(2 + N);
        C[make_pair(2, 2 + N)] = 2;
        C[make_pair(2 + N, Sink)] = 2;

        int maxFlow = getMaxFlow(G, Source, Sink);
        //cerr << "max Flow " << maxFlow << '\n';
        if(maxFlow == 2)
            cout << "YES\n";
        else cout << "NO\n";

        C.clear();
        for(int i = 0 ; i <= 2 * N + 1 ; ++ i)
            vector <int> ().swap(G[i]);
    }
    return 0;
}
