#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <bitset>

using namespace std;

const int maxn = 100015;

ifstream fin("disconnect.in");
ofstream fout("disconnect.out");

vector <int> g[maxn], path[maxn], arb[maxn];
int n, m, pathwh[maxn], pathpos[maxn], pathfather[maxn], subtree[maxn], paths, level[maxn];

inline void dfs(int node, int father) {
	int son = -1;
	subtree[node] = 1;
	level[node] = level[father] + 1;
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
		if(*it == father)
			continue;
		dfs(*it, node);
		subtree[node] += subtree[*it];
		if(son == -1 || subtree[son] < subtree[*it])
			son = *it;
	}
	if(son == -1) {
		pathwh[node] = ++ paths;
		pathfather[pathwh[node]] = father;
		path[pathwh[node]].push_back(node);
		return;
	}
	pathwh[node] = pathwh[son];
	pathfather[pathwh[node]] = father;
	path[pathwh[node]].push_back(node);
}

inline void update(int node, int st, int dr, int x, int ind, int value) {
	if(st == dr) {
		arb[ind][node] = value;
		return ;
	}
	int mid = ((st + dr) >> 1);
	if(x <= mid)
		update(node << 1, st, mid, x, ind, value);
	else
		update((node << 1) | 1, mid + 1, dr, x, ind, value);
	arb[ind][node] = arb[ind][node << 1] + arb[ind][(node << 1) | 1];
}

inline void removeEdge(int x, int y) {
	if(level[x] < level[y])
		swap(x, y);
	update(1, 0, path[pathwh[x]].size() - 1, pathpos[x], pathwh[x], 1);
}

inline int sum(int node, int st, int dr, int x, int y, int ind) {
	if(x <= st && dr <= y)
		return arb[ind][node];
	int mid = ((st + dr) >> 1);
	int ret = 0;
	if(x <= mid)
		ret += sum(node << 1, st, mid, x, y, ind);
	if(mid < y)
		ret += sum((node << 1) | 1, mid + 1, dr, x, y, ind);
	return ret;
}

inline int queryheavypath(int x, int y) {
	if(pathwh[x] == pathwh[y]) {
		if(pathpos[x] > pathpos[y])
			swap(x, y);
		if(pathpos[x] == pathpos[y])
			return 0;
		return sum(1, 0, path[pathwh[x]].size() - 1, pathpos[x] + 1, pathpos[y], pathwh[x]);
	}
	if(level[pathfather[pathwh[x]]] < level[pathfather[pathwh[y]]])
		swap(x, y);
	return queryheavypath(pathfather[pathwh[x]], y) + sum(1, 0, path[pathwh[x]].size() - 1, 0, pathpos[x], pathwh[x]);
}

inline bool query(int x, int y) {
	return queryheavypath(x, y) == 0;
}

int main() {

    fin >> n >> m;
    for(int i = 1 ; i < n ; ++ i) {
        int x, y;
        fin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    dfs(1, 0);

	for(int i = 1 ; i <= paths ; ++ i) {
		reverse(path[i].begin(), path[i].end());
		fout << "path = " << i << '\n';
		for(int j = 0 ; j < path[i].size() ; ++ j)
			pathpos[path[i][j]] = j, fout << path[i][j] << ' ';
		fout << '\n';
		arb[i].resize(path[i].size() << 3);
	}

    int V = 0;

    for (int i = 0; i < m; ++i) {
        int type, x, y; fin >> type >> x >> y;

        int a = x xor V;
        int b = y xor V;

        if (type == 1) {
            removeEdge(a, b);
        } else
            if (query(a, b)) {
                fout << "YES\n";
                V = a;
            } else {
                fout << "NO\n";
                V = b;
            }
    }
}
