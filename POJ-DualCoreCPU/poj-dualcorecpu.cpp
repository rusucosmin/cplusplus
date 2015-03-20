#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <queue>

using namespace std;

const int maxn = 20005;
const int oo = 0x3f3f3f3f;

int n, m, edgecnt, father[maxn], dadedge[maxn];
vector <pair<int, int> > g[maxn];
vector <int> cap;
bitset <maxn> used;
queue <int> q;

inline void addedge(int x, int y, int c, int rc = 0) {
	g[x].push_back(make_pair(y, edgecnt));
	cap.push_back(c);
	++ edgecnt;
	g[y].push_back(make_pair(x, edgecnt));
	cap.push_back(rc);
	++ edgecnt;
}

inline bool bfs(int source, int sink) {
	used.reset();
	q.push(source);
	used[source] = 1;
	while(!q.empty()) {
		int node = q.front();
		q.pop();
		if(node == sink)
			continue;
		for(vector <pair<int, int> > :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
			if(!used[it->first] && cap[it->second] > 0) {
				used[it->first] = 1;
				father[it->first] = node;
				dadedge[it->first] = it->second;
				q.push(it->first);
			}
	}
	return used[sink];
}

inline int getmaxflow(int source, int sink) {
	int maxflow = 0;
	while(bfs(source, sink))
		for(vector <pair<int, int> > :: iterator it = g[sink].begin() ; it != g[sink].end() ; ++ it) {
			if(!used[it->first] || cap[it->second ^ 1] <= 0)
				continue;
			father[sink] = it->first;
			dadedge[sink] = it->second ^ 1;
			int bottleneck = oo;
			for(int i = sink ; i != source ; i = father[i])
				bottleneck = min(bottleneck, cap[dadedge[i]]);
			if(!bottleneck)
				continue;
			for(int i = sink ; i != source ; i = father[i]) {
				cap[dadedge[i]] -= bottleneck;
				cap[dadedge[i] ^ 1] += bottleneck;
			}
			maxflow += bottleneck;
		}
	return maxflow;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("poj-dualcorecpu.in", "r", stdin);
	freopen("poj-dualcorecpu.out", "w", stdout);
	#endif
	scanf("%d%d", &n, &m);
	int source = 0, sink = n + 1;
	for(int i = 1 ; i <= n ; ++ i) {
		int a, b;
		scanf("%d%d", &a, &b);
		addedge(source, i, a);
		addedge(i, sink, b);
	}
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		addedge(x, y, z, z);
	}
	cout << getmaxflow(source, sink) << '\n';
}
