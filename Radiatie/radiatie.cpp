#include <fstream>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

const int maxn = 15005;
const int maxl = 16;

int n, m, k, father[maxn], dp[maxl][maxn], ancestor[maxl][maxn], level[maxn];
vector <pair<int, pair<int, int > > > edges;
vector <pair<int, int> > g[maxn];

inline int find(int x) {
	if(x != father[x])
		father[x] = find(father[x]);
	return father[x];
}

void dfs(int node, int dad) {
	ancestor[0][node] = dad;
	level[node] = level[dad] + 1;
	for(auto it : g[node])
		if(it.first != dad) {
			dp[0][it.first] = it.second;
			dfs(it.first, node);
		}
}

inline int query(int x, int y) {
	if(level[x] < level[y])
		swap(x, y);
	int log1, log2;
	
	for(log1 = 1 ; (1 << log1) < level[x] ; ++ log1);
	for(log2 = 1 ; (1 << log2) < level[y] ; ++ log2);

	int ans = 0;
	for(int i = log1 ; i >= 0 ; -- i)
		if(level[x] - (1 << i) >= level[y]) {
			ans = max(ans, dp[i][x]);
			x = ancestor[i][x];
		}
	if(x == y)
		return ans;
	
	for(int i = log2 ; i >= 0 ; -- i)
		if(ancestor[i][x] != ancestor[i][y]) {
			ans = max(ans, dp[i][x]);
			ans = max(ans, dp[i][y]);
			x = ancestor[i][x];
			y = ancestor[i][y];
		}
	ans = max(ans, dp[0][x]);
	ans = max(ans, dp[0][y]);
	return ans;
}

int main() {
	ifstream fin("radiatie.in");
	ofstream fout("radiatie.out");

	fin >> n >> m >> k;

	while (m -- ) {
		int x, y, z;
		fin >> x >> y >> z;
		edges.push_back(make_pair(z, make_pair(x, y)));
	}
	sort(edges.begin(), edges.end());
	for(int i = 1 ; i <= n ; ++ i)
		father[i] = i;
	for(auto it : edges) {
		int tx = find(it.second.first);
		int ty = find(it.second.second);
		if(tx != ty) {
			father[tx] = ty;
			g[it.second.first].push_back(make_pair(it.second.second, it.first));
			g[it.second.second].push_back(make_pair(it.second.first, it.first));
		}
	}

	dfs(1, 0);
	
	for(int i = 1 ; (1 << i) <= n ; ++ i)
		for(int j = 1 ; j <= n ; ++ j) {
			ancestor[i][j] = ancestor[i - 1][ ancestor[i - 1][j] ];
			dp[i][j] = max(dp[i - 1][j], dp[i - 1][ ancestor[i - 1][j] ]);	
		}
	
	while (k -- ) {
		int x, y;
		fin >> x >> y;
		fout << query(x, y) << '\n';
	}


}
