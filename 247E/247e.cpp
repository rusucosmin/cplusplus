#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <bitset>
#include <queue>
#include <unordered_map>

using namespace std;

const int maxn = 155;
const int oo = 0x3f3f3f3f;
const int sigma = 26;

string t;
unordered_map<int, int> fr;
vector <pair<int, int> > g[maxn];
int cap[maxn][maxn], n, father[maxn], dist[maxn];
bitset <maxn> inq;

inline int getb(int x) {
	return n + x + 1;
}

inline void addedge(int x, int y, int c, int cost) {
	g[x].push_back(make_pair(y, cost));
	cap[x][y] = c;
	g[y].push_back(make_pair(x, -cost));
	cap[y][x] = 0;
}

inline bool bellmanford(int source, int sink) {
	queue <int> q;
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
		for(auto it : g[node]) {
			if(dist[it.first] > dist[node] + it.second && cap[node][it.first] > 0) {
				dist[it.first] = dist[node] + it.second;
				father[it.first] = node;
				if(inq[it.first])
					continue;
				inq[it.first] = 1;
				q.push(it.first);
			}
		}
	}
	return dist[sink] != oo;
}

inline pair<int, int> getmincostmaxflow(int source, int sink) {
	int ans = 0;
	int mf = 0;
	while(bellmanford(source, sink)) {
		int bottleneck = oo;
		for(int i = sink ; i != source ; i = father[i])
			bottleneck = min(bottleneck, cap[father[i]][i]);
		for(int i = sink; i != source ; i = father[i]) {
			cap[father[i]][i] -= bottleneck;
			cap[i][father[i]] += bottleneck;
		}
		ans += bottleneck * dist[sink];
		mf += bottleneck;
	}
	return make_pair(mf, ans);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("247e.in", "r", stdin);
	freopen("247e.out", "w", stdout);
	#endif
	cin >> t;
	cin >> n;
	int source = 0;
	int sink = getb(sigma);
	int total = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		string s;
		int x;
		cin >> s >> x;
		for(auto it : s)
			++ fr[it - 'a'];
		for(int j = 0 ; j < sigma ; ++ j) {
			if(!fr[j])
				continue;
			addedge(i, getb(j), fr[j], i);
		}
		fr.clear();
		addedge(source, i, x, 0);
	}
	for(auto it : t)
		++ fr[it - 'a'];
	for(int i = 0 ; i < sigma ; ++ i) {
		if(!fr[i])
			continue;
		addedge(getb(i), sink, fr[i], 0); 
		total += fr[i];
	}
	pair<int, int> ans = getmincostmaxflow(source, sink);
	if(ans.first != total)
		cout << "-1\n";
	else cout << ans.second << '\n';
}
