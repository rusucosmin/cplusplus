#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <queue>
#include <string.h>

using namespace std;

const int oo = 0x3f3f3f3f;
const int maxn = 305;

int n, m, father[maxn], cap[maxn][maxn];
vector <int> g[maxn];
bitset <maxn> used;

inline void addedge(int x, int y, int c, int rc) {
	g[x].push_back(y);
	g[y].push_back(x);
	cap[x][y] = c;
	cap[y][x] = rc;
}

inline bool bfs(int source, int sink) {
	queue <int> q;
	used.reset();
	q.push(source);
	used[source] = 1;
	while(!q.empty()) {
		int node = q.front();
		q.pop();
		if(node == sink)
			continue;
		for(auto it : g[node])
			if(!used[it] && cap[node][it] > 0) {
				used[it] = 1;
				father[it] = node;
				q.push(it);
			}
	}
	return used[sink];
}

inline int getmaxflow(int source, int sink) {
	int maxflow = 0;
	while(bfs(source, sink))
		for(vector <int> :: iterator it = g[sink].begin(); it != g[sink].end() ; ++ it) {
			if(!used[*it] || cap[*it][sink] <= 0)
				continue;
			father[sink] = *it;
			int bottleneck = oo;
			for(int i = sink ; i != source ; i = father[i])
				bottleneck = min(bottleneck, cap[father[i]][i]);
			if(!bottleneck)
				continue;
			for(int i = sink ; i != source ; i = father[i]) {
				cap[father[i]][i] -= bottleneck;
				cap[i][father[i]] += bottleneck;
			}
			maxflow += bottleneck;
		}
	return maxflow;	
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("spoj-coconut.in", "r", stdin);
	freopen("spoj-coconut.out", "w", stdout);
	#endif
	cin.sync_with_stdio(false);
	while(cin >> n >> m) {
		if(!n && !m)
			return 0;
		int source = 0, sink = n + 1;
		for(int i = 1 ; i <= n ; ++ i) {
			int x;
			cin >> x;
			if(x == 0)
				addedge(source, i, 1, 0);
			else
				addedge(i, sink, 1, 0);
		}
		for(int i = 1 ; i <= m ; ++ i) {
			int x, y;
			cin >> x >> y;
			addedge(x, y, 1, 1);
		}
		cout << getmaxflow(source, sink) << '\n';
		for(int i = source ; i <= sink ; ++ i)
			vector <int> ().swap(g[i]);
		memset(cap, 0, sizeof(cap));
	}
}
