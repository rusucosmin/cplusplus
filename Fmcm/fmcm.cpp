#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;

const int maxn = 355;
const int oo = 0x3f3f3f3f;

struct edge {
	int nxt, cap, flow, cost;
	edge(int _nxt, int _cap, int _flow, int _cost) {
		nxt = _nxt;
		cap = _cap;
		flow = _flow;
		cost = _cost;
	}
};

int n, m, father[maxn], dadedge[maxn], edgecnt;
vector <int> g[maxn];
vector <edge> e;

inline void addedge(int x, int y, int cap, int flow, int cost) {
	g[x].push_back(edgecnt ++);
	e.push_back(edge(y, cap, flow, cost));
}

queue <int> q;
int dist[maxn];
bitset <maxn> inq;

inline bool bellmanford(int source, int sink) {
	memset(dist, oo, sizeof(dist));
	q.push(source);
	dist[source] = 0;
	inq[source] = 1;
	while(!q.empty()) {
		int node = q.front();
		q.pop();
		inq[node] = 0;
		if(node == sink)
			continue;
		for(auto it : g[node]) {
			int nxt = e[it].nxt;
			int cap = e[it].cap;
			int flow = e[it].flow;
			int cost = e[it].cost;
			if(dist[nxt] > dist[node] + cost && cap > flow) {
				dist[nxt] = dist[node] + cost;
				father[nxt] = node;
				dadedge[nxt] = it;
				if(inq[nxt])
					continue;
				inq[nxt] = 1;
				q.push(nxt);
			}
		}
	}
	return dist[sink] != oo;
}

inline int getmincostmaxflow(int source, int sink) {
	int mincostmaxflow = 0;
	while(bellmanford(source, sink)) {
		int bottleneck = oo;
		for(int i = sink ; i != source ; i = father[i])
			bottleneck = min(bottleneck, e[dadedge[i]].cap - e[dadedge[i]].flow);
		for(int i = sink ; i != source ; i = father[i]) {
			e[dadedge[i]].flow += bottleneck;
			e[dadedge[i] ^ 1].flow -= bottleneck;
		}
		mincostmaxflow += bottleneck * dist[sink];	
	}
	return mincostmaxflow;
}

int main() {
	ifstream fin("fmcm.in");
	ofstream fout("fmcm.out");
	int source, sink;
	fin >> n >> m >> source >> sink;
	for(int i = 1 ; i <= m ; ++ i) {
		int a, b, c, d;
		fin >> a >> b >> c >> d;
		addedge(a, b, c, 0, d);
		addedge(b, a, 0, 0,-d);
	}
	fout << getmincostmaxflow(source, sink) << '\n';
}
