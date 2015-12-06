#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("lca.in");
ofstream fout("lca.out");

const int maxn = 100005;
const int maxlg = 25;

int n, m, anc[maxlg][maxn], level[maxn];

inline int query(int x, int y) {
	if(level[x] < level[y])
		swap(x, y);
	int diff = level[x] - level[y];
	for(int i = 0 ; i < maxlg ; ++ i)
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

inline void solve_stramosi() {
	ifstream fin("lca.in");
	ofstream fout("lca.out");
	fin >> n >> m;
	level[1] = 1;
	for(int i = 2 ; i <= n ; ++ i) {
		fin >> anc[0][i];
		level[i] = level[anc[0][i]] + 1;
	}
	for(int i = 1 ; i < maxlg ; ++ i)
		for(int j = 1 ; j <= n ; ++ j)
			anc[i][j] = anc[i - 1][anc[i - 1][j]];
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		fin >> x >> y;
		fout << query(x, y) << '\n';
	}
}

vector <int> g[maxn];
int w[maxn], path[maxn], paths, dad[maxn];

inline void dfs(int node, int father) {
	level[node] = level[father] + 1;
	w[node] = 1;
	int heaviest = -1;
	for(auto it : g[node]) {
		dfs(it, node);
		w[node] += w[it];
		if(heaviest == -1)
			heaviest = it;
		else
			if(w[heaviest] < w[it])
				heaviest = it;
	}
	if(heaviest == -1)
		path[node] = ++ paths;
	else
		path[node] = path[heaviest];
	dad[path[node]] = father;
}

inline int queryhpd(int x, int y) {
	if(path[x] == path[y]) {
		if(level[x] < level[y])
			swap(x, y);
		return y;
	}
	if(level[dad[path[x]]] < level[dad[path[y]]])
		swap(x, y);
	return queryhpd(dad[path[x]], y);
}

inline void solve_hpd() {
	ifstream fin("lca.in");
	ofstream fout("lca.out");
	fin >> n >> m;
	for(int i = 2 ; i <= n ; ++ i) {
		int x;
		fin >> x;
		g[x].push_back(i);
	}
	dfs(1, 0);
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		fin >> x >> y;
		fout << queryhpd(x, y) << '\n';
	}
}

int rmq[maxlg][maxn << 1], euler[maxn << 1], lvl[maxn << 1], k, lg[maxn << 1], first[maxn];

inline void dfs2(int node, int father) {
	level[node] = level[father] + 1;	
	first[node] = ++ k;
	euler[k] = node;
	lvl[k] = level[node];
	for(auto it : g[node]) {
		dfs2(it, node);	
		euler[++ k] = node;
		lvl[k] = level[node];
	}
}

inline int querylca(int x, int y) {
	x = first[x];
	y = first[y];
	if(x > y)
		swap(x, y);
	int l = lg[y - x + 1];
	int ret = rmq[l][x];
	if(lvl[ret] > lvl[rmq[l][y - (1 << l) + 1]])
		ret = rmq[l][y - (1 << l) + 1];
	return euler[ret];
}

inline void solve_rmq() {
	ifstream fin("lca.in");
	ofstream fout("lca.out");
	fin >> n >> m;
	for(int i = 2 ; i <= n ; ++ i) {
		int x;
		fin >> x;
		g[x].push_back(i);
	}
	dfs2(1, 0);
	for(int i = 1 ; i <= k ; ++ i)
		rmq[0][i] = i;
	for(int i = 2 ; i <= k ; ++ i)
		lg[i] = lg[i >> 1] + 1;
	for(int i = 1 ; (1 << i) <= k ; ++ i) {
		int aux = (1 << (i - 1));
		for(int j = 1 ; j + (1 << i) - 1 <= k ; ++ j) {
			rmq[i][j] = rmq[i - 1][j];
			if(lvl[rmq[i][j]] > lvl[rmq[i - 1][j + aux]])
				rmq[i][j] = rmq[i - 1][j + aux];
		}
	}
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		fin >> x >> y;
		fout << querylca(x, y) << '\n';
	}
}

int main() {
	///solve_stramosi();
	solve_hpd();
	///solve_rmq();
}
