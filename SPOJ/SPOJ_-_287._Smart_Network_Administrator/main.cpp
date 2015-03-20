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
#include <cassert>

using namespace std;

const char infile[] = "input.in";
const char outfile[] = "output.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 505;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, K, Source = 1, Sink;
vector <int> Houses;
vector <pair<int, int> > Edges;
int C[MAXN][MAXN], Father[MAXN], T;
bitset <MAXN> Used;
queue <int> Q;
Graph G;

inline bool BF(Graph G, int Source, int Sink) {
    Q.push(Source);
    Used.reset();
    Used[Source] = 1;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        if(Node == Sink)
            continue;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(C[Node][*it] > 0 && !Used[*it]) {
                Used[*it] = 1;
                Father[*it] = Node;
                Q.push(*it);
            }
    }
    return Used[Sink];
}

inline int getMaxFlow(Graph &G, int Source, int Sink) {
    int maxFlow = 0;
    while(BF(G, Source, Sink))
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

inline bool Check(int mid) {
    C[Source][1] = K;
    C[1][Source] = 0;
    for(vector<pair<int, int> > :: iterator it = Edges.begin(), fin = Edges.end(); it != fin ; ++ it) {
        C[it->first][it->second] = mid;
        C[it->second][it->first] = mid;
    }
    for(vector<int> :: iterator it = Houses.begin(), fin = Houses.end(); it != fin ; ++ it) {
        C[*it][Sink] = 1;
        C[Sink][*it] = 0;
    }
    return getMaxFlow(G, Source, Sink) == K;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        cin >> N >> M >> K;
        Sink = N + 1;
        for(int i = 1 ; i <= K ; ++ i) {
            int x;
            cin >> x;
            Houses.push_back(x);
            G[x].push_back(Sink);
            G[Sink].push_back(x);
        }
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y;
            cin >> x >> y;
            Edges.push_back(make_pair(x, y));
            G[x].push_back(y);
            G[y].push_back(x);
        }
        G[Source].push_back(1);
        G[1].push_back(Source);
        int st = 0, dr = K + 1;
        int Ans = -1;
        int _cnt = 0;
        while(st <= dr) {
            int mid = ((st + dr) >> 1);
            ++ _cnt;
            assert(_cnt <= 100);
            if(Check(mid)) {
                dr = mid - 1;
                Ans = mid;
            }
            else st = mid + 1;
        }
        cout << Ans << '\n';
        for(int i = 0 ; i <= N + 1 ; ++ i)
            vector <int>().swap(G[i]);
        memset(C, 0, sizeof(C));
        vector <int>().swap(Houses);
        vector <pair<int, int> > ().swap(Edges);
    }
    return 0;
}
