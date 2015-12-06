#include <iostream>
#include <fstream>
#include <algorithm>
#include <bitset>
#include <queue>
#include <string.h>
#include <unordered_map>

using namespace std;

ifstream fin("cmcm.in");
ofstream fout("cmcm.out");

const int maxn = 605;
const int oo = 0x3f3f3f3f;

struct edge {
	int nxt, cap, cost, flow;
	int ind;
	edge(int _nxt, int _cap, int _flow, int _cost, int _ind = 0) {
		nxt = _nxt;
		cap = _cap;
		cost = _cost;
		flow = _flow;
		ind = _ind;
	}
};

int n, m, ed, edgecnt, father[maxn], dadedge[maxn], dist[maxn];
vector <int> g[maxn];
vector <edge> e;
bitset <maxn> inq;
queue <int> q;

inline int getleft(int x) {
	return x;
}

inline int getright(int x) {
	return x + n;
}

inline void addedge(int x, int y, int cap, int flow, int cost, int _ind = 0) {
	g[x].push_back(edgecnt ++ );
	e.push_back(edge(y, cap, flow, cost, _ind));
}

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
			int cost = e[it].cost;
			int cap = e[it].cap;
			int flow = e[it].flow;
			if(cap > flow && dist[nxt] > dist[node] + cost){
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

inline void getmincostmaxflow(int source, int sink) {
	int maxflow = 0, mincostmaxflow = 0;
	while(bellmanford(source, sink)) {
		int bottleneck = oo;
		for(int i = sink ; i != source ; i = father[i])
			bottleneck = min(bottleneck, e[dadedge[i]].cap - e[dadedge[i]].flow);
		for(int i = sink ; i != source ; i = father[i]) {
			e[dadedge[i]].flow += bottleneck;
			e[dadedge[i] ^ 1].flow -= bottleneck;
		}
		maxflow += bottleneck;
		mincostmaxflow += bottleneck * dist[sink];
	}
	fout << maxflow << ' ' << mincostmaxflow << '\n';
}

int main() {
	fin >> n >> m >> ed;
	int source = 0, sink = n + m + 1;
	for(int i = 1 ; i <= ed ; ++ i) {
		int x, y, cost;
		fin >> x >> y >> cost;
		addedge(getleft(x), getright(y), 1, 0, cost, i);
		addedge(getright(y), getleft(x), 0, 0,-cost);
	}
	for(int i = 1 ; i <= n ; ++ i) {
		addedge(source, getleft(i), 1, 0, 0);
		addedge(getleft(i), source, 0, 0, 0);
	}
	for(int i = 1 ; i <= m ; ++ i) {
		addedge(getright(i), sink, 1, 0, 0);
		addedge(sink, getright(i), 0, 0, 0);
	}
	getmincostmaxflow(source, sink);
	for(int i = 1 ; i <= n ; ++ i) {
		for(auto it : g[i]) {
			if(e[it].flow && e[it].nxt != source) {
				fout << e[it].ind << ' ';
				break;
			}
		}
	}
}
