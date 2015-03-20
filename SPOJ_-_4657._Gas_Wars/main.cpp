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

const int MAXN = 115;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int T, N, M, g, I, K, D, Source, Sink;
int C[MAXN][MAXN], F[MAXN][MAXN], Father[MAXN];
Graph G;
bitset <MAXN> Used;
vector <pair<pair<int, int>, int> > Edges;
vector <int> Sources;
vector <int> Sinks;
vector <int> v;
queue <int> Q;

inline void buildGraph(int maxVal) {
    memset(C, 0, sizeof(C));
    memset(F, 0, sizeof(F));
    for(int i = 0 ; i <= N + 2 ; ++ i)
        vector < int > ().swap(G[i]);
    for(vector <pair<pair<int, int>, int> > :: iterator it = Edges.begin(), fin = Edges.end(); it != fin ; ++ it) {
        if(it->second <= maxVal) {
            G[it->first.first].push_back(it->first.second);
            G[it->first.second].push_back(it->first.first);
            C[it->first.first][it->first.second] = it->second;
            C[it->first.second][it->first.first] = it->second;
        }
    }
    for(int i = 0 ; i < Sinks.size() ; ++ i) {
        G[Sinks[i]].push_back(Sink);
        G[Sink].push_back(Sinks[i]);
        C[Sinks[i]][Sink] = g;
        C[Sink][Sinks[i]] = g;
    }
    for(int i = 0 ; i < Sources.size() ; ++ i) {
        G[Source].push_back(Sources[i]);
        G[Sources[i]].push_back(Source);
        C[Source][Sources[i]] = g;
        C[Sources[i]][Source] = g;
    }
    G[Sink + 1].push_back(Source);
    G[Source].push_back(Sink + 1);
    C[Sink + 1][Source] = g;
    C[Source][Sink + 1] = g;
}

inline bool BFs(Graph &G, int Source, int Sink, int maxVal) {
    Used.reset();
    Q.push(Source);
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

inline int getMaxFlow(Graph &G, int Source, int Sink, int maxVal) {
    int maxFlow = 0;
    buildGraph(maxVal);
    while(BFs(G, Source, Sink, maxVal))
        for(It it = G[Sink].begin(), fin = G[Sink].end(); it != fin ; ++ it)
        if(Used[*it] && C[*it][Sink] - F[*it][Sink] > 0) {
                Father[Sink] = *it;
                int bottleNeck = oo;
                for(int i = Sink ; i != Source ; i = Father[i])
                    bottleNeck = min(bottleNeck, C[Father[i]][i] - F[Father[i]][i]);
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
    cin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        cin >> N >> M >> K >> I >> g;
        Source = 0;
        Sink = N + 1;
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y, z;
            cin >> x >> y >> z;
            Edges.push_back(make_pair(make_pair(x, y), z));
            v.push_back(z);
        }
        for(int i = 1 ; i <= K ; ++ i) {
            int x;
            cin >> x;
            Sources.push_back(x);
        }
        for(int i = 1 ; i <= I ; ++ i) {
            int x;
            cin >> x;
            Sinks.push_back(x);
        }
        sort(v.begin(), v.end());
        int st = 0, dr = v.size() - 1, Ans = -1;
        while(st <= dr) {
            int mid = ((st + dr) >> 1);
            int maxFlow = getMaxFlow(G, Sink + 1, Sink, v[mid]);
            if(maxFlow == g) {
                Ans = v[mid];
                dr = mid - 1;
            }
            else st = mid + 1;
        }
        if(Ans != -1)
            Ans *= 100;
        cout << Ans << '\n';

        v.clear();
        Sources.clear();
        Sinks.clear();
        Edges.clear();
    }
    fin.close();
    fout.close();
    return 0;
}
