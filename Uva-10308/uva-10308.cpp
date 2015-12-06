#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <queue>
#include <sstream>
#include <iostream>

using namespace std;

const int maxn = 10005;

vector <pair<int, int> > g[maxn];
long long dist[maxn];
int deepest;

inline void dfs(int node, int father) {
	if(dist[deepest] < dist[node])
		deepest = node;
	for(auto it : g[node]) {
		if(it.first == father)
			continue;
		dist[it.first] = dist[node] + it.second;
		dfs(it.first, node);
	}
}

inline void solve() {
	deepest = 1;
	dfs(1, 0);
	dist[deepest] = 0;
	dfs(deepest, 0);
	cout << dist[deepest] << '\n';
	for(int i = 0 ; i < maxn ; ++ i)
		vector <pair<int, int> > ().swap(g[i]);
}

int main() {
	string s;
	while(getline(cin, s)) {
		if(s == "") {
			solve();
			continue;
		}
		istringstream get(s);
		int x, y, z;
		get >> x >> y >> z;
		g[x].push_back(make_pair(y, z));
		g[y].push_back(make_pair(x, z));
	}
	solve();
}
