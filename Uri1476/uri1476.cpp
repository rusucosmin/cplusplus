#include <fstream>
#include <vector>
#include <iostream>
#include <string.h>
#include <queue>
#include <algorithm>

using namespace std;

const int maxn = 20005;
const int maxlg = 20;

int n, m, s, father[maxn], level[maxn], ancestor[maxlg][maxn], dp[maxlg][maxn];
vector <pair<int, int> > g[maxn];
vector <pair<int, pair<int, int> > > edges;

inline int find(int x) {
	if(father[x] != x)
		father[x] = find(father[x]);
	return father[x];
}

inline int query(int x, int y) {
	if(level[x] < level[y])
		swap(x, y);
	
	int log1, log2;
	for(log1 = 1 ; (1 << log1) < level[x] ; ++ log1);
	for(log2 = 1 ; (1 << log2) < level[y] ; ++ log2);

	int ans = 0x3f3f3f3f;
	for(int k = log1 ; k >= 0 ; -- k)
		if(level[x] - (1 << k) >= level[y]) {
			ans = min(ans, dp[k][x]);
			x = ancestor[k][x];
		}
	if(x == y)
		return ans;
	for(int k = log2 ; k >= 0 ; -- k) {
		if(ancestor[k][x] != ancestor[k][y]) {
			ans = min(ans, dp[k][x]);
			ans = min(ans, dp[k][y]);
			x = ancestor[k][x];
			y = ancestor[k][y];
		}
	}
	ans = min(ans, dp[0][x]);
	ans = min(ans, dp[0][y]);
	return ans;
}
	   
inline void dfs(int node) {
	level[node] = level[ancestor[0][node]] + 1;
	for(vector <pair<int, int> > :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
		if(it->first != ancestor[0][node]) {
			ancestor[0][it->first] = node;
			dp[0][it->first] = it->second;
			dfs(it->first);
		}	
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uri1476.in", "r", stdin);
	freopen("uri1476.out", "w", stdout);
	#endif
	while(cin >> n >> m >> s) {
		for(int i = 1 ; i <= m ; ++ i) {
			int x, y, z;
			cin >> x >> y >> z;
			edges.push_back(make_pair(z, make_pair(x, y)));
		}
		sort(edges.begin(), edges.end(), greater<pair<int, pair<int, int> > >());
		for(int i = 1 ; i <= n ; ++ i) {
			vector <pair<int, int> >().swap(g[i]);
			father[i] = i;
		}
		memset(dp, 0, sizeof(dp));
		memset(ancestor, 0, sizeof(ancestor));
		memset(level, 0, sizeof(level));
		for(vector <pair<int, pair<int, int> > > :: iterator it = edges.begin() ; it != edges.end() ; ++ it) {
			int tx = find(it->second.first);
			int ty = find(it->second.second);
			if(tx == ty)
				continue;
			father[tx] = ty;
			g[it->second.first].push_back(make_pair(it->second.second, it->first));
			g[it->second.second].push_back(make_pair(it->second.first, it->first));
		}
		dfs(1);
		for(int k = 1 ; (1 << k) <= n ; ++ k)
			for(int i = 1 ; i <= n ; ++ i) {
				ancestor[k][i] = ancestor[k - 1][ancestor[k - 1][i]];
				dp[k][i] = min(dp[k - 1][i], dp[k - 1][ancestor[k - 1][i]]);
			}
		for(int i = 1 ; i <= s ; ++ i) {
			int x, y;
			cin >> x >> y;
			cout << query(x, y) << '\n';
		}
		vector<pair<int, pair<int, int> > > ().swap(edges);
	}
	
}
