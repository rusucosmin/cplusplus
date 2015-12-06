#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 100005;
const int oo = 0x3f3f3f3f;

ifstream fin("heavypath.in");
ofstream fout("heavypath.out");

int n, m, val[maxn], weight[maxn], pathwhere[maxn], pathfather[maxn], pathpos[maxn], paths, level[maxn];
vector <int> g[maxn], path[maxn], arb[maxn];

inline void dfs(int node, int father) {
	weight[node] = 1;
	level[node] = level[father] + 1;
	int fr = -1;
	for(auto it : g[node]) {
		if(it == father)
			continue;
		dfs(it, node);
		weight[node] += weight[it];
		if(fr == -1)
			fr = it;
		else if(weight[fr] < weight[it])
			fr = it;
	}
	if(fr == -1)
		pathwhere[node] = ++ paths;
	else
		pathwhere[node] = pathwhere[fr];
	path[pathwhere[node]].push_back(node);
	pathfather[pathwhere[node]] = father;
}

inline void build(int node, int st, int dr, int where) {
	if(st == dr) {
		arb[where][node] = val[path[where][st]];
		return;
	}
	int mid = ((st + dr) >> 1);
	build(node << 1, st, mid, where);
	build((node << 1) | 1, mid + 1, dr, where);
	arb[where][node] = max(arb[where][node << 1], arb[where][(node << 1) | 1]);
}

inline void update(int node, int st, int dr, int pos, int value, int where) {
	if(st == dr) {
		arb[where][node] = value;
		return ;
	}
	int mid = ((st + dr) >> 1);
	if(pos <= mid)
		update(node << 1, st, mid, pos, value, where);
	else
		update((node << 1) | 1, mid + 1, dr, pos, value, where);
	arb[where][node] = max(arb[where][node << 1], arb[where][(node << 1) | 1]);
}

inline int query(int node, int st, int dr, int x, int y, int where) {
	if(x <= st && dr <= y)
		return arb[where][node];
	int mid = ((st + dr) >> 1);
	int ret = -oo;
	if(x <= mid)
		ret = max(ret, query(node << 1, st, mid, x, y, where));
	if(mid < y)
		ret = max(ret, query((node << 1) | 1, mid + 1, dr, x, y, where));
	return ret;
}

inline int queryhpd(int x, int y) {
	if(pathwhere[x] == pathwhere[y]) {
		if(pathpos[x] > pathpos[y])
			swap(x, y);
		return query(1, 0, path[pathwhere[x]].size() - 1, pathpos[x], pathpos[y], pathwhere[x]);
	}
	if(level[pathfather[pathwhere[x]]] < level[pathfather[pathwhere[y]]])
		swap(x, y);
	int act = query(1, 0, path[pathwhere[x]].size() - 1, 0, pathpos[x], pathwhere[x]);
	return max(act, queryhpd(pathfather[pathwhere[x]], y));
}

int main() {
	fin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i)
		fin >> val[i];
	for(int i = 1 ; i < n ; ++ i) {
		int x, y;
		fin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(1, 0);
	for(int i = 1 ; i <= paths ; ++ i) {
		reverse(path[i].begin(), path[i].end());
		for(int j = 0 ; j < path[i].size() ; ++ j)
			pathpos[path[i][j]] = j;
		arb[i].resize(path[i].size() << 2);
		build(1, 0, path[i].size() - 1, i);
	}
	for(int i = 1 ; i <= m ; ++ i) {
		int op, x, y;
		fin >> op >> x >> y;
		if(op == 0)
			update(1, 0, path[pathwhere[x]].size() - 1, pathpos[x], y, pathwhere[x]);
		else
			fout << queryhpd(x, y) << '\n';
	}
}
