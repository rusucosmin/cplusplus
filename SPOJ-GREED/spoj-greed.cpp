#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <string.h>

using namespace std;

const int maxn = 1005;
const int oo = 0x3f3f3f3f;

struct edge {
	int cap, flow, cost;
	edge(int _cap, int _flow, int _cost) {
		cap = _cap;
		flow = _flow;
		cost = _cost;
	}
};

int t, n, m, cnt[maxn], cap[maxn][maxn], edgecnt, a[maxn], dist[maxn], father[maxn], dadedge[maxn];
vector <pair<int, int> > g[maxn];
bitset <maxn> inq, used;
queue <int> q;
vector <edge> e;

inline void addedge(int x, int y, int c, int cost) {
	g[x].push_back(make_pair(y, edgecnt));
	e.push_back(edge(c, 0, cost));
	++ edgecnt;

	g[y].push_back(make_pair(x, edgecnt));
	e.push_back(edge(0, 0, -cost));
	++ edgecnt;
}

inline bool bellmanford(int source, int sink) {
	memset(dist, oo, sizeof(dist));
	q.push(source);
	inq[source] = 1;
	dist[source] = 0;
	while(!q.empty()) {
		int node = q.front();
		q.pop();
		inq[node] = 0;
		if(node == sink)
			continue;
		for(auto it : g[node]) {
			if(dist[it.first] > dist[node] + e[it.second].cost && e[it.second].cap - e[it.second].flow > 0) {
				dist[it.first] = dist[node] + e[it.second].cost; 
				father[it.first] = node;
				dadedge[it.first] = it.second;
				if(inq[it.first])	
					continue;
				inq[it.first] = 1;
				q.push(it.first);
			}
		}
	}
	return dist[sink] != oo;
}

inline int getmincostmaxflow(int source, int sink) {
	int ans = 0;
	while(bellmanford(source, sink)) {
		int bottleneck = oo;
		for(int i = sink ; i != source ; i = father[i])
			bottleneck = min(bottleneck, e[dadedge[i]].cap - e[dadedge[i]].flow);
		for(int i = sink ; i != source ; i = father[i]) {
			e[dadedge[i]].flow += bottleneck;
			e[dadedge[i] ^ 1].flow -= bottleneck;
		}
		ans += bottleneck * dist[sink];
	}
	return ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("spoj-greed.in", "r", stdin);
	freopen("spoj-greed.out", "w", stdout);
	#endif
	cin >> t;
	while(t --) {
		cin >> n;
		for(int i = 1 ; i <= n ; ++ i) {
			cin >> a[i];
			++ cnt[a[i]];
		}
		int source = 0, sink = 2*n + 1;
		for(int i = 1 ; i <= n ; ++ i) {
			addedge(source, i, cnt[i], 0);	
			addedge(i, i + n, cnt[i], 0);
			addedge(i + n, sink, 1, 0);
		}
		cin >> m;
		for(int i = 1 ; i <= m ; ++ i) {
			int x, y;
			cin >> x >> y;
			addedge(x + n, y + n, (1 << 20), 1);
			addedge(y + n, x + n, (1 << 20), 1);
		}
		cout << getmincostmaxflow(source, sink) << '\n';
		for(int i = 0 ; i <= sink ; ++ i)
			vector <pair<int, int> > ().swap(g[i]);
		edgecnt = 0;
		vector <edge>().swap(e);
		memset(cnt, 0, sizeof(cnt));
	}
}
