#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <string.h>
#include <queue>

using namespace std;

const int maxn = 5005;
const int oo = 0x3f3f3f3f;

vector <pair<int, int> > g[maxn];
vector <int> cap;
int n, m, father[maxn], dadedge[maxn], edgecnt;
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
	used[source] = 1;
	q.push(source);
	while(!q.empty()) {
		int node = q.front();
		q.pop();
		if(node == sink)	
			continue;
		for(vector <pair<int, int> > :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
			if(!used[it->first] && cap[it->second] > 0) {
				used[it->first] = 1;
				father[it->first] = node;
				dadedge[it->first] = it->second;
				q.push(it->first);
			}
		}
	}
	return used[sink];
}

inline long long getmaxflow(int source, int sink) {
	long long maxflow = 0;
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
	freopen("spoj-fastflow.in", "r", stdin);
	freopen("spoj-fastflow.out", "w", stdout);
	#endif
	cin.sync_with_stdio(false);
	cin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y, z;
		cin >> x >> y >> z;
		if(x == y)
			continue;
		addedge(x, y, z, z);
	}
	cout << getmaxflow(1, n) << '\n';
}
