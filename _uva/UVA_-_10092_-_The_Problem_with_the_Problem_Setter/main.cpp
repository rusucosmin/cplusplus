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

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int NK, NP, total, Source, Sink, Father[MAXN];
map<pair<int, int> , int> C, F;
bitset <MAXN> Used;
queue <int> Q;
Graph G;

inline bool BFs(Graph &G, int Source, int Sink) {
    Used.reset();
    Q.push(Source);
    Used[Source] = true;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        if(Node == Sink)
            continue;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(!Used[*it] && C[make_pair(Node,*it)] - F[make_pair(Node,*it)] > 0) {
                Used[*it] = true;
                Father[*it] = Node;
                Q.push(*it);
            }
    }
    return Used[Sink];
}

inline int getMaxFlow(Graph &G, int Source, int Sink) {
    int maxFlow = 0;
    while(BFs(G, Source, Sink)) {
        for(It it = G[Sink].begin(), fin = G[Sink].end(); it != fin ; ++ it) {
            if(!Used[*it] || C[make_pair(*it, Sink)] - F[make_pair(*it, Sink)] <= 0)
                continue;
            Father[Sink] = *it;
            int bottleNeck = oo;
            for(int i = Sink ; i != Source ; i = Father[i])
                bottleNeck = min(bottleNeck, C[make_pair(Father[i], i)] - F[make_pair(Father[i], i)]);
            if(!bottleNeck)
                continue;
            for(int i = Sink ; i != Source ; i = Father[i]) {
                F[make_pair(Father[i], i)] += bottleNeck;
                F[make_pair(i, Father[i])] -= bottleNeck;
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
    while(cin >> NK >> NP) {
        if(!NK && !NP)
            return 0;
        total = 0;
        Source = 0;
        Sink = NK + NP + 1;
        for(int i = 1 ; i <= NK ; ++ i) {
            int x;
            cin >> x;
            total += x;
            G[i + NP].push_back(Sink);
            G[Sink].push_back(i + NP);
            C[make_pair(i + NP, Sink)] = x;
        }
        for(int i = 1 ; i <= NP ; ++ i) {
            int x, y;
            cin >> x;
            for(int j = 1 ; j <= x ; ++ j) {
                cin >> y;
                G[i].push_back(y + NP);
                G[y + NP].push_back(i);
                C[make_pair(i, y + NP)] = 1;
            }
            G[Source].push_back(i);
            G[i].push_back(Source);
            C[make_pair(Source, i)] = 1;
        }
        int maxFlow = getMaxFlow(G, Source, Sink);
        if(maxFlow == total) {
            cout << "1\n";
            for(int i = 1 ; i <= NK ; ++ i) {
                for(int j = 1 ; j <= NP ; ++ j)
                    if(F[make_pair(j, i + NP)])
                        cout << j << ' ';
                cout << '\n';
            }
        }
        else cout << "0\n";
        for(int i = Source ; i <= Sink ; ++ i)
            vector <int>().swap(G[i]);
        map<pair<int, int>, int>().swap(C);
        map<pair<int, int>, int>().swap(F);
    }
    return 0;
}
