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
#include <tr1/unordered_map>

using namespace std;
using namespace tr1;

const char infile[] = "monede.in";
const char outfile[] = "monede.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 130;
const int oo = 0x3f3f3f3f;

typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, S, C, a[MAXN][MAXN], Avg;
int Source, Sink;

class Graph {
public:
    Graph() {
    }
    Graph(int N) {
        g.resize(N);
        dist.resize(N);
        inq.resize(N);
        father.resize(N);
    }
    void addEdge(int x, int y, int capacity, int cost = 0) {
        g[x].push_back(make_pair(y, cost));
        g[y].push_back(make_pair(x,-cost));
        c[x][y] += capacity;
    }
    bool bellmanford(int source, int sink) {
        fill(inq.begin(), inq.end(), false);
        fill(dist.begin(), dist.end(), oo);
        dist[source] = 0;
        q.push(source);
        inq[source] = true;
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            inq[node] = false;
            for(vector <pair<int, int> > :: iterator it = g[node].begin(), fin = g[node].end(); it != fin ; ++ it)
                if(dist[it->first] > dist[node] + it->second && c[node][it->first] > 0) {
                    dist[it->first] = dist[node] + it->second;
                    father[it->first] = node;
                    if(inq[it->first])
                        continue;
                    inq[it->first] = true;
                    q.push(it->first);
                }
        }
        return dist[sink] != oo;
    }
    int getMinCostMaxFlow(int source, int sink) {
        int minCostMaxFlow = 0;
        while(bellmanford(source, sink)) {
            int bottleneck = oo;
            for(int i = sink ; i != source ; i = father[i])
                bottleneck = min(bottleneck, c[father[i]][i]);
            for(int i = sink ; i != source ; i = father[i]) {
                c[father[i]][i] -= bottleneck;
                c[i][father[i]] += bottleneck;
            }
            minCostMaxFlow += bottleneck * dist[sink];
        }
        return minCostMaxFlow;
    }
private:
    vector <vector <pair<int, int> > > g;
    vector <int> dist, father;
    queue <int> q;
    vector <bool> inq;
    unordered_map <int, unordered_map <int, int> > c;
} G;

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    fin >> N >> M;
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= M ; ++ j) {
            fin >> a[i][j];
            if(a[i][j]) {
                ++ C;
                S += a[i][j];
            }
        }
    Avg = S / C;
    Source = 0;
    Sink = N * M + 1;
    G = Graph(Sink + 1);
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= M ; ++ j) {
            if(!a[i][j])
                continue;
            if(a[i][j] > Avg) {
                G.addEdge(Source, (i - 1) * M + j, a[i][j] - Avg);
                for(int newi = 1 ; newi <= N ; ++ newi)
                    for(int newj = 1 ; newj <= M ; ++ newj)
                        if(a[newi][newj] < Avg && a[newi][newj])
                            G.addEdge((i - 1) * M + j, (newi - 1) * M + newj, oo, abs(newi - i) + abs(newj - j) + 1);
            }
            if(a[i][j] < Avg)
                G.addEdge((i - 1) * M + j, Sink, Avg - a[i][j]);
        }
    fout << G.getMinCostMaxFlow(Source, Sink) << '\n';
    fin.close();
    fout.close();
    return 0;
}
