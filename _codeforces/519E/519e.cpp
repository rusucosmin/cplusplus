#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int maxn = 100005;
const int maxlg = 22;

int anc[maxlg][maxn], level[maxn];
int n, m, subarb[maxn];
vector <int> g[maxn];

inline void dfs(int node, int father) {
	level[node] = level[father] + 1;
	subarb[node] = 1;
	anc[0][node] = father;
	for(auto it : g[node]) {
		if(it == father)
			continue;
		dfs(it, node);
		subarb[node] += subarb[it];
	}
}

inline int kthanc(int k, int x) {
	for(int i = 0 ; i < maxlg ; ++ i)
		if(k & (1 << i))
			x = anc[i][x];
	return x;
}

inline int lca(int x, int y) {
	int diff = level[x] - level[y];
	x = kthanc(diff, x);
	if(x == y)
		return x;
	for(int i = maxlg - 1 ; i >= 0 ; -- i)
		if(anc[i][x] != anc[i][y]) {
			x = anc[i][x];
			y = anc[i][y];
		}
	return anc[0][x];
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("519e.in", "r", stdin);
	freopen("519e.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i < n ; ++ i) {
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(1, 0);
	for(int i = 1 ; i < maxlg ; ++ i)
		for(int j = 1 ; j <= n ; ++ j)
			anc[i][j] = anc[i - 1][anc[i - 1][j]];
	cin >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		cin >> x >> y;
		if(level[x] < level[y])
			swap(x, y);
		int _lca = lca(x, y);
		int d1 = level[x] - level[_lca];
		int d2 = level[y] - level[_lca];
		if((d1 + d2) % 2 == 1) {
			cout << "0\n";
			continue;
		}
		if(d1 == d2) {
			x = kthanc(d1 - 1, x);
			y = kthanc(d2 - 1, y);
			cout << n - subarb[x] - subarb[y] << '\n';
		}
		else {
			x = kthanc((d1 + d2) / 2 - 1, x);
			cout << subarb[anc[0][x]] - subarb[x] << '\n';
		}
	}
}
