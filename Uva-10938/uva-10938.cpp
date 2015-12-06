#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 5005;
const int maxlg = 15;

vector <int> g[maxn];
int n, anc[maxlg][maxn], level[maxn];

inline void dfs(int node, int father) {
	anc[0][node] = father;
	level[node] = level[father] + 1;
	for(auto it : g[node])
		if(it != father)
			dfs(it, node);
}

inline int lca(int x, int y) {
	int dif = level[x] - level[y];
	for(int i = 0 ; i < maxlg ; ++ i)
		if(dif & (1 << i))
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

inline int kanc(int x, int k) {
	for(int i = 0 ; i < maxlg ; ++ i)
		if(k & (1 << i))
			x = anc[i][x];
	return x;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uva-10938.in", "r", stdin);
	freopen("uva-10938.out", "w", stdout);
	#endif
	while(cin >> n) {
		if(n == 0)
			return 0;
		for(int i = 1 ; i < n ; ++ i) {
			int x, y;
			cin >> x >> y;
			g[x].push_back(y);
			g[y].push_back(x);
		}
		dfs(1, 0);
		for(int i = 1 ; (1 << i) <= n ; ++ i)
			for(int j = 1 ; j <= n ; ++ j)
				anc[i][j] = anc[i - 1][anc[i - 1][j]];
		int m;
		cin >> m;
		while(m --) {
			int x, y;
			cin >> x >> y;
			if(level[x] < level[y])
				swap(x, y);
			int _lca = lca(x, y);
			int d1 = level[x] - level[_lca];
			int d2 = level[y] - level[_lca];
			if((d1 + d2) % 2 == 0)
				cout << "The fleas meet at " << kanc(x, (d1 + d2) / 2) << ".\n";
			else {
				int x1 = kanc(x, (d1 + d2) / 2);
				int x2 = kanc(x, (d1 + d2) / 2 + 1);
				if(x1 > x2)
					swap(x1, x2);
				cout << "The fleas jump forever between " << x1 << " and "
				 << x2 << ".\n";
			}
		}
		for(int i = 1 ; i <= n ; ++ i)
			vector <int> ().swap(g[i]);
	}
	
}
