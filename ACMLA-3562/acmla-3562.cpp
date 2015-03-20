#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <queue>
#include <bitset>
#include <iomanip>

using namespace std;

const int maxn = 105;
const double oo = 0x3f3f3f3f;

struct edge {
	int x, cap;
	int cost;
	edge(int _x, int _cap, int _cost) {
		x = _x;
		cap = _cap;
		cost = _cost;
	}
};

vector <int> g[2][maxn];
vector <edge> e[2];
int n, m, edgecnt[2];

inline void addedge(int where, int x, int y, int cap, int cost = 0) {
	g[where][x].push_back(edgecnt[where]);
	e[where].push_back(edge(y, cap, cost));
	++ edgecnt[where];
	g[where][y].push_back(edgecnt[where]);
	e[where].push_back(edge(x, 0, -cost));
	++ edgecnt[where];
}

int dist[maxn];
bitset <maxn> inq;
int father[maxn], dadedge[maxn];

inline bool bellmanford(int type, int source, int sink) {
	for(int i = source ; i <= sink ; ++ i)
		dist[i] = oo;
	queue <int> q;
	inq.reset();
	q.push(source);
	dist[source] = 0;
	inq[source] = 1;
	while(!q.empty()) {
		int node = q.front();
		q.pop();
		inq[node] = 0;
		if(node == sink)
			continue;
		for(vector <int> :: iterator it = g[type][node].begin() ; it != g[type][node].end() ; ++ it) {
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


inline long long getmincostmaxflow(int type, int source, int sink) {
	int mincost = 0;
	while(bellmanford(type, source, sink)) {
		int bottleneck = oo;
		for(int i = sink ; i != source ; i = father[i])
			bottleneck = min(bottleneck, e[type][dadedge[i]].cap);
		for(int i = sink ; i != source ; i = father[i]) {
			e[type][dadedge[i]].cap -= bottleneck;
			e[type][dadedge[i] ^ 1].cap += bottleneck;
		}
		mincost += 1LL*bottleneck * dist[sink];
	}
	return mincost;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("acmla-3562.in", "r", stdin);
	freopen("acmla-3562.out", "w", stdout);
	#endif
	cin.sync_with_stdio(false);
	int test = 0;
	while(cin >> n >> m) {
		if(!n && !m)
			return 0;
		int source = 0, sink = n + m + 1;
		for(int i = 1 ; i <= n ; ++ i) {
			int x;
			cin >> x;
			addedge(0, source, i, x); 
			addedge(1, source, i, x);
		}
		for(int i = 1 ; i <= m ; ++ i) {
			int x;
			cin >> x;
			addedge(0, i + n, sink, x);
			addedge(1, i + n, sink, x);
		}
		for(int i = 1 ; i <= n ; ++ i)
			for(int j = 1 ; j <= m ; ++ j) {
				double aux;
				cin >> aux;
				if(aux == -1)
					continue;
				int x = (aux * 100 + 0.5);
				addedge(0, i, j + n, (1 << 10),  x);
				addedge(1, i, j + n, (1 << 10), -x);
		}
		int minans = getmincostmaxflow(0, source, sink);
		int maxans = -1 * getmincostmaxflow(1, source, sink);
		printf("Problem %d: %.2lf to %.2lf\n",++test,(double)minans / 100.0,(double) maxans / 100.0);
		for(int i = 0 ; i < 2 ; ++ i) {
			for(int j = source ; j <= sink ; ++ j)
				vector <int> ().swap(g[i][j]);
			edgecnt[i] = 0;
			vector <edge>().swap(e[i]);
		}
	}
}
