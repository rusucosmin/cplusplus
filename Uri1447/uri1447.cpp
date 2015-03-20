#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include <unordered_map>
#include <queue>
#include <bitset>

using namespace std;

const int maxn = 105;

struct edge {
	int nxt;
	int cap;
	int cost;
	int ind;
	edge(int _nxt, int _cap, int _cost, int _ind) {
		nxt = _nxt;
		cap = _cap;
		cost = _cost;
		ind = _ind;
	}
};

int n, m, d, k, idx, dp[maxn], father[maxn], dadedge[maxn];
unordered_map<int, unordered_map<int, int> > c; 
vector < int > g[maxn];
vector <edge> e;
queue <int> q;
bitset <maxn> inq;

inline bool bellmanford(int source, int sink) {
	memset(dp, 0x3f3f3f3f, sizeof(dp));

	q.push(source);
	inq[source] = 1;
	dp[source] = 0;

	int debug = 0;
	while (!q.empty()) {
		int node = q.front();
		q.pop();
		inq[node] = 0;
		if(node == sink)
			continue;

		for(vector <int> :: iterator it = g[node].begin();it!=g[node].end();++it) {
			if(e[*it].cap > 0 && dp[e[*it].nxt] > dp[node] + e[*it].cost) {
				dp[e[*it].nxt] = dp[node] + e[*it].cost;
				father[e[*it].nxt] = node;
				dadedge[e[*it].nxt] = e[*it].ind;
				if(!inq[e[*it].nxt]) {
					q.push(e[*it].nxt);
					inq[e[*it].nxt] = 1;
				}
			}
		}
	}
	if(dp[sink] == 0x3f3f3f3f)
		return 0;
	return 1;
}

int mincostmaxflow;

inline int getmincostmaxflow(int source, int sink) {
	mincostmaxflow = 0;
	int	maxflow = 0;
	int debug = 0;
	while(bellmanford(source, sink)) {
		int bottleneck = 0x3f3f3f3f;
		for(int i = sink ; i != source ; i = father[i]) {
			int in = dadedge[i];
			bottleneck = min(bottleneck, e[in].cap);
		}
		for(int i = sink ; i != source ; i = father[i]) {
			int in = dadedge[i];
			e[in].cap -= bottleneck;
			e[in ^ 1].cap += bottleneck;
		}
		mincostmaxflow += bottleneck * dp[sink];
		maxflow += bottleneck;
	}
	return maxflow;
}

inline void addEdge(int x, int y, int cost, int cap) {
	e.push_back(edge(y, cap, cost, idx));
	g[x].push_back(idx);
	idx ++;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uri1447.in", "r", stdin);
	freopen("uri1447.out", "w", stdout);
	#endif
	int test = 0;
	while(cin >> n >> m) {
		vector <pair<int, pair<int, int> > > input;
		e.clear();
		for(int i = 1 ; i <= n ; ++ i)
			vector <int>().swap(g[i]);
		idx = 0;
		for(int i = 1 ; i <= m ; ++ i) {
			int x, y, z;
			cin >> x >> y >> z;
			input.push_back(make_pair(x, make_pair(y, z)));
		}
		cin >> d >> k;
		for(int i = 0 ; i < m ; ++ i) {
			int x = input[i].first;
			int y = input[i].second.first;
			int z = input[i].second.second;

			addEdge(x, y, z, k);
			addEdge(y, x,-z, 0);
			addEdge(y, z, z, k);
			addEdge(x, y,-z, 0);
		}
		
		addEdge(0, 1, 0, d);
		int x = getmincostmaxflow(0, n);


		cout << "Instancia " << ++ test << '\n';
		if(x == d)
			cout << mincostmaxflow << '\n';
		else
			cout << "impossivel\n";

		cout << '\n';

	}
}
