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
#include <bitset>
#include <tr1/unordered_map>

using namespace std;
using namespace tr1;

const char infile[] = "trafic.in";
const char outfile[] = "trafic.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 160;
const int oo = 0x3f3f3f3f;

typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

class Graph {
public:
    Graph() {
    }
    Graph(int N) {
        g.resize(N);
        used.resize(N);
        father.resize(N);
    }
    void _clear() {
        c.clear();
    }
    void addEdge(int x, int y, int capacity) {
        g[x].push_back(y);
        c[x][y] = capacity;
    }
    inline bool bfs(int source, int sink) {
        fill(used.begin(), used.end(), false);
        queue <int> q;
        q.push(source);
        used[source] = true;
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            for(It it = g[node].begin(), fin = g[node].end(); it != fin ; ++ it)
                if(!used[*it] && c[node][*it] > 0) {
                    used[*it] = 1;
                    q.push(*it);
                    father[*it] = node;
                }
        }
        return used[sink];
    }
    int getMaxFlow(int source, int sink, int g) {
        int maxFlow = 0;
        while(bfs(source, sink)) {
            for(int i = sink ; i != source ; i = father[i]) {
                -- c[father[i]][i];
                ++ c[i][father[i]];
            }
            ++ maxFlow;
            if(maxFlow > g)
                return maxFlow;
        }
        return maxFlow;
    }
private:
    vector <vector <int> > g;
    vector <int> father;
    unordered_map<int, unordered_map<int, int> > c;
    vector <bool> used;
} graph;

vector <pair<int, int> > G[MAXN];
queue <int> q;
bitset <MAXN> inq;
vector <int> sourcedist, sinkdist;
int N, M, g;

inline void getDistances(int source, vector <int> &dist) {
    q.push(source);
    inq[source] = 1;
    fill(dist.begin(), dist.end(), oo);
    dist[source] = 0;
    while(!q.empty()) {
        int node = q.front();
        inq[node] = false;
        q.pop();

        for(vector <pair<int, int> > :: iterator it = G[node].begin(), fin = G[node].end(); it != fin ; ++ it) {
            if(dist[it->first] > dist[node] + it->second) {
                dist[it->first] = dist[node] + it->second;
                if(inq[it->first])
                    continue;
                inq[it->first] = true;
                q.push(it->first);
            }
        }
    }
}

int main() {
    vector<pair< pair<int, int>, int> > Edges;
    fin >> N >> M >> g;
    graph = Graph(N);
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        fin >> x >> y >> z;
        -- x;
        -- y;
        G[x].push_back(make_pair(y, z));
        G[y].push_back(make_pair(x, z));
        Edges.push_back(make_pair(make_pair(x, y), z));
    }
    sourcedist.resize(N);
    sinkdist.resize(N);
    getDistances(0, sourcedist);
    getDistances(N - 1, sinkdist);

    double st = 0.0, dr = sourcedist[N - 1];

	double ans = -1.0;
    while(dr - st > 0.0001) {
        double mid = ((st + dr) / 2.0);
        graph._clear();
        for(vector <pair<pair<int, int>, int> > :: iterator it = Edges.begin(), fin = Edges.end(); it != fin ; ++ it) {
            int x = it->first.first;
            int y = it->first.second;
            int z = it->second;
            if(sourcedist[x] + sinkdist[y] > sourcedist[y] + sinkdist[x])
                swap(x, y);
            int dist = sourcedist[x] + sinkdist[y];
            if(((1.0 * (dist + z)) / 2.0) < mid)
                graph.addEdge(x, y, 1);
            else graph.addEdge(x, y, oo);
        }
		int tmp = graph.getMaxFlow(0, N - 1, g);
        if(tmp <= g) {
			ans = mid;
            dr = mid;
		}
        else st = mid;
    }
	if(ans == -1.0)
		fout << "-1\n";
	else
    	fout << fixed << setprecision(1) << ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
