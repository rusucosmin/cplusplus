#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
#include <bitset>

using namespace std;

const int maxn = 205;

int c[maxn][maxn], f[maxn][maxn], n, comp, a[maxn], source, sink, father[maxn];
queue <int> q;
bitset <maxn> used;
vector <int> g[maxn], h[maxn], ans[maxn];

inline bool isprime(int x) {
	for(int d = 2 ; d * d <= x ; ++ d)
		if(x % d == 0)
			return false;
	return true;
}

inline bool bfs() {
	queue <int> q;
	used.reset();
	q.push(source);
	used[source] = 1;
	while(!q.empty()) {
		int node = q.front();
		q.pop();
		if(node == sink)
			continue;
		for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
			if(!used[*it] && c[node][*it] - f[node][*it] > 0) {
				used[*it] = 1;
				q.push(*it);
				father[*it] = node;
			}
	}
	return used[sink];
}

inline int getmaxflow() {
	int maxflow = 0;
	while(bfs())
		for(vector <int> :: iterator it = g[sink].begin() ; it != g[sink].end() ; ++ it) {
			if(!used[*it] || (c[*it][sink] - f[*it][sink] <= 0))
				continue;
			father[sink] = *it;
			int bottleneck = 0x3f3f3f3f;
			for(int i = sink ; i != source ; i = father[i])
				bottleneck = min(bottleneck, c[father[i]][i] - f[father[i]][i]);
			if(!bottleneck)
				continue;
			for(int i = sink ; i != source ; i = father[i]) {
				f[father[i]][i] += bottleneck;
				f[i][father[i]] -= bottleneck;
			}
			maxflow += bottleneck;
		}
	return maxflow;
}

inline void dfs(int node, int comp) {
	used[node] = 1;
	ans[comp].push_back(node);
	for(vector <int> :: iterator it = h[node].begin() ; it != h[node].end() ; ++ it)
		if(!used[*it])
			dfs(*it, comp);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("510e.in", "r", stdin);
	freopen("510e.out", "w", stdout);
	#endif

	cin >> n;
	source = 0;
	sink = n + 1;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> a[i];
	for(int i = 1 ; i <= n ; ++ i) {
		if(a[i] % 2 == 0) {
			g[source].push_back(i);
			g[i].push_back(source);
			c[source][i] = 2;
		}
		else {
			g[i].push_back(sink);
			g[sink].push_back(i);
			c[i][sink] = 2;
		}
		for(int j = 1 ; j <= n ; ++ j)
			if(isprime(a[i] + a[j])) {
				if(a[i] % 2 == 0)
					c[i][j] = 1;
				else
					c[j][i] = 1;
				g[i].push_back(j);
				g[j].push_back(i);
			}
	}
	int mf = getmaxflow();
	cerr << mf << '\n';
	if(mf != n) {
		cout << "Impossible\n";
		return 0;
	}
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= n ; ++ j)
			if(f[i][j]) {
				h[i].push_back(j);
				h[j].push_back(i);
			}
	used.reset();
	for(int i = 1 ; i <= n ; ++ i)
		if(!used[i])
			dfs(i, ++ comp);
	cout << comp << '\n';
	for(int i = 1 ; i <= comp ; ++ i, cout << '\n') {
		cout << ans[i].size() << ' ';
		for(auto it : ans[i])
			cout << it << ' ';
	}
}
