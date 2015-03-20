#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int maxn = 100005;
const int maxlg = 20;

int n, m, k, aib[maxn * 2], father[maxn], level[maxn], in[maxn], out[maxn], anc[maxlg][maxn];
vector <int> g[maxn];
pair<int, int> edge[maxn];

inline void dfs(int node, int father) {
	level[node] = level[father] + 1;
	in[node] = ++ k;
	for(auto it : g[node])
		if(it != father) {
			anc[0][it] = node;
			for(int i = 1 ; i < maxlg ; ++ i)
				anc[i][it] = anc[i - 1][anc[i - 1][it]];
			dfs(it, node);
		}
	out[node] = ++ k;
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

inline int lsb(int x) {
	return x & (-x);
}

inline void insert(int pos, int value) {
	for(int i = pos ; i <= k ; i += lsb(i))
		aib[i] += value;
}

inline int sum(int x) {
	int sum = 0;
	for(int i = x ; i > 0 ; i -= lsb(i))
		sum += aib[i];
	return sum;
}

inline int sum_interval(int x, int y) {
	return sum(y) - sum(x - 1);
}

inline int query(int x, int y) {
	int _lca = lca(x, y);	
	if(sum_interval(in[_lca] + 1, in[x]) || sum_interval(in[_lca] + 1, in[y]))
		return -1;
	return level[x] + level[y] - 2 * level[_lca];
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("165d.in", "r", stdin);
	freopen("165d.out", "w", stdout);
	#endif
	cin.sync_with_stdio(false);
	cin >> n;
	for(int i = 1 ; i < n ; ++ i) {
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
		edge[i] = make_pair(x, y);
	}
	dfs(1, 0);
	cin >> m;	
	for(int i = 1 ; i <= m ; ++ i) {
		int op, x, y;
		cin >> op;
		if(op == 1) {
			cin >> x;
			if(level[edge[x].first] > level[edge[x].second])
				x = edge[x].first;
			else
				x = edge[x].second;
			insert(in[x], -1);
			insert(out[x], 1);
		}
		else if(op == 2) {
			cin >> x;
			if(level[edge[x].first] > level[edge[x].second])
				x = edge[x].first;
			else
				x = edge[x].second;
			insert(in[x], 1);
			insert(out[x], -1);
		}
		else {
			cin >> x >> y;
			cout << query(x, y) << '\n';
		}

	}
}
