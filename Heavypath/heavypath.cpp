#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 100005;

int n, m, a[maxn], w[maxn], paths, pathfather[maxn], pathwhere[maxn], pathpos[maxn], level[maxn];
vector <int> path[maxn], g[maxn];
vector <int> arb[maxn];

inline void dfs(int node, int father) {
	int heaviest = -1;
	level[node] = level[father] + 1;
	w[node] = 1;
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
		if(*it == father)
			continue;
		dfs(*it, node);
		w[node] += w[*it];
		if(heaviest == -1)
			heaviest = *it;
		else
			if(w[heaviest] < w[*it])
				heaviest = *it;
	}
	if(heaviest == -1) {
		pathwhere[node] = ++ paths;
		pathfather[pathwhere[node]] = father;
		path[pathwhere[node]].push_back(node);
		return ;
	}
	pathwhere[node] = pathwhere[heaviest];
	pathfather[pathwhere[node]] = father;
	path[pathwhere[node]].push_back(node);
}

inline void build(int node, int st, int dr, int type) {
	if(st == dr) {
		arb[type][node] = a[path[type][st]];
		return ;
	}
	int mid = ((st + dr) >> 1);
	build(node << 1, st, mid, type);
	build((node << 1) | 1, mid + 1, dr, type);
	arb[type][node] = max(arb[type][node << 1], arb[type][(node << 1) | 1]);
}

inline void update(int node, int st, int dr, int pos, int type) {
	if(st == dr) {
		arb[type][node] = a[path[type][st]];
		return ;
	}
	int mid = ((st + dr) >> 1);
	if(pos <= mid)
		update(node << 1, st, mid, pos, type);
	else
		update((node << 1) | 1, mid + 1, dr, pos, type);
	arb[type][node] = max(arb[type][node << 1], arb[type][(node << 1) | 1]);
}

inline int query(int node, int st, int dr, int a, int b, int type) {
	if(a <= st && dr <= b)
		return arb[type][node];
	int mid = ((st + dr) >> 1);
	int ret = -0x3f3f3f3f;
	if(a <= mid)
		ret = max(ret, query(node << 1, st, mid, a, b, type));
	if(mid < b)
		ret = max(ret, query((node << 1) | 1, mid + 1, dr, a, b, type));
	return ret;
}

inline int queryhp(int x, int y) {
	if(pathwhere[x] == pathwhere[y]) {
		if(pathpos[x] > pathpos[y])
			swap(x, y);
		return query(1, 0, path[pathwhere[x]].size() - 1, pathpos[x], pathpos[y], pathwhere[x]);
	}
	if(level[pathfather[pathwhere[x]]] < level[pathfather[pathwhere[y]]])
		swap(x, y);
	int actmax = query(1, 0, path[pathwhere[x]].size() - 1, 0, pathpos[x], pathwhere[x]);
	return max(actmax, queryhp(pathfather[pathwhere[x]], y));
}

int main() {
	ifstream fin("heavypath.in");
	ofstream fout("heavypath.out");
	fin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i)
		fin >> a[i];
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
		int type, x, y;
		fin >> type;
		if(type == 0) {
			fin >> x >> y;	
			a[x] = y;
			update(1, 0, path[pathwhere[x]].size() - 1, pathpos[x], pathwhere[x]);
		}
		else {
			fin >> x >> y;
			fout << queryhp(x, y) << '\n';
		}
	}
}
