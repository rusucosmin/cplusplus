#include <iostream>
#include <vector>

using namespace std;

const int maxn = 200005;
const int maxlg = 22;

int n, k, level[maxn], anc[maxlg][maxn], mars[maxn];
vector <int> g[maxn];

inline void dfs(int node, int father) {
	anc[0][node] = father;
	level[node] = level[father] + 1;
	for(auto it : g[node])
		if(it != father)
			dfs(it, node);
}

inline void dfssolve(int node, int father) {
	for(auto it : g[node])
		if(it != father) {
			dfssolve(it, node);
			mars[node] += mars[it];
		}
}

inline int lca(int x, int y) {
	if(level[x] < level[y])
		swap(x, y);
	int diff = level[x] - level[y];
	for(int i = 0 ; (1 << i) <= diff ; ++ i)
		if(diff & (1 << i))
			x = anc[i][x];
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
	freopen("191c.in", "r", stdin);
	freopen("191c.out", "w", stdout);
	#endif

	vector<pair<int, int> > edges;
	cin >> n;
	for(int i = 1 ; i < n ; ++ i) {
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
		edges.push_back(make_pair(x, y));
	}
	dfs(1, 0);
	for(int i = 1 ; i < maxlg ; ++ i)
		for(int j = 1 ; j <= n ; ++ j)
			anc[i][j] = anc[i - 1][anc[i - 1][j]];
	cin >> k;
	for(int i = 1 ; i <= k ; ++ i) {
		int x, y;
		cin >> x >> y;
		++ mars[x];
		++ mars[y];
		mars[lca(x, y)] -= 2;
	}
	dfssolve(1, 0);
	mars[1] = 0;
	for(auto it : edges) {
		int x = it.first;
		int y = it.second;
		if(level[x] < level[y])
			swap(x, y);
		cout << mars[x] << ' ';
	}

}
