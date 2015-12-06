#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <string.h>

using namespace std;

const int maxn = 3005;
const int oo = 0x3f3f3f3f;

struct edge {
	int x, cap, cost;
	edge(int _x, int _cap, int _cost) {
		x = _x;
		cap = _cap;
		cost = _cost;
	}
};

vector <int> g[2][maxn];
int n, k, edgecnt[2], father[maxn], dadedge[maxn], dist[maxn];
vector <edge> e[2];
queue <int> q;
bitset <maxn> inq;

inline int getleft(int i) {
	return i;
}

inline int getright(int x) {
	return n + x + 1251;
}

inline void addedge(int type, int x, int y, int c, int cost) {
	g[type][x].push_back(edgecnt[type]);
	e[type].push_back(edge(y, c, cost));	
	++ edgecnt[type];
	g[type][y].push_back(edgecnt[type]);
	e[type].push_back(edge(x, 0, -cost));
	++ edgecnt[type];
}

inline bool bellmanford(int type, int source, int sink) {
	memset(dist, oo, sizeof(dist));
	dist[source] = 0;
	q.push(source);
	inq[source] = 1;
	while(!q.empty()) {
		int node = q.front();
		q.pop();
		inq[node] = 0;
		if(node == sink)
			continue;
		for(vector<int> :: iterator it = g[type][node].begin() ; it != g[type][node].end() ; ++ it) {
			edge nxt = e[type][*it];
			if(dist[nxt.x] > dist[node] + nxt.cost && nxt.cap > 0) {
				dist[nxt.x] = dist[node] + nxt.cost;
				father[nxt.x] = node;
				dadedge[nxt.x] = *it;
				if(inq[nxt.x])
					continue;
				inq[nxt.x] = 1;
				q.push(nxt.x);
			}
		}
	}
	return dist[sink] != oo;
}

inline int getmincostmaxflow(int type, int source, int sink) {
	int ans = 0;
	int maxflow = 0;
	while(bellmanford(type, source, sink)) {
		int bottleneck = oo;
		for(int i = sink ; i != source ; i = father[i])
			bottleneck = min(bottleneck, e[type][dadedge[i]].cap);
		for(int i = sink ; i != source ; i = father[i]) {
			e[type][dadedge[i]].cap -= bottleneck;
			e[type][dadedge[i] ^ 1].cap += bottleneck;
		}
		ans += bottleneck * dist[sink];
		maxflow += bottleneck;
	}
	return ans;
}

int main() {
	freopen("naveplanare.in", "r", stdin);
	freopen("naveplanare.out", "w", stdout);
	cin >> n >> k;
	int source = 0, sink = getright(1201), supersource = getright(1202);
	for(int i = 1 ; i <= n ; ++ i) {
		int x, y;
		cin >> x >> y;

		addedge(0, getleft(i), getright(x), 1, 0);
		addedge(1, getleft(i), getright(y), 1, 0); 

		addedge(0, source, getleft(i), 1, 0);
		addedge(1, source, getleft(i), 1, 0);
	}
	for(int x = -1200 ; x <= 1200 ; ++ x) {
		addedge(0, getright(x - 1), getright(x), oo, 1);
		addedge(0, getright(x), getright(x - 1), oo, 1);

		addedge(1, getright(x - 1), getright(x), oo, 1);
		addedge(1, getright(x), getright(x - 1), oo, 1);

		addedge(0, getright(x), sink, 1, 0);
		addedge(1, getright(x), sink, 1, 0);
	}
	addedge(0, supersource, source, k, 0);
	addedge(1, supersource, source, k, 0);
	cout << getmincostmaxflow(0, supersource, sink) + getmincostmaxflow(1, supersource, sink) << '\n';
}
