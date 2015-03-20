#include <fstream>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 10005;

vector <int> g[maxn];
vector <pair<int, int> > bridges;
int n, m, q, lowlink[maxn], dflevel[maxn], father[maxn];

inline void dfs(int node, int father, int level) {
	dflevel[node] = lowlink[node] = level;

	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
		if(*it == father)
			continue;
		if(!dflevel[*it]) {
			dfs(*it, node, level + 1);
			lowlink[node] = min(lowlink[node], lowlink[*it]);
			if(lowlink[*it] > dflevel[node])
				bridges.push_back(make_pair(node, *it));
		}
		else
			lowlink[node] = min(lowlink[node], dflevel[*it]);
	}
}

inline int find(int x) {
	if(father[x] != x)
		father[x] = find(father[x]);
	return father[x];
}

inline void unite(int x, int y) {
	int tx = find(x);
	int ty = find(y);
	if(tx == ty)
		return ;
	father[tx] = ty;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uri1314.in", "r", stdin);
	freopen("uri1314.out", "w", stdout);
	#endif
	while(true) {
		cin >> n >> m >> q;
		if(n + m + q == 0)
			return 0;
		for(int i = 0 ; i < m ; ++ i) {
			int x, y;
			cin >> x >> y;
			g[x].push_back(y);
			g[y].push_back(x);
		}
		for(int i = 1 ; i <= n ; ++ i) {
			father[i] = i;
			if(!dflevel[i])
				dfs(i, i, 1);
		}	
		for(vector <pair<int, int > > :: iterator it = bridges.begin() ; it != bridges.end() ; ++ it)
			unite(it->first, it->second);
		while (q --) {
			int a, b;
			cin >> a >> b;
			if(find(a) == find(b))
				cout << "Y\n";
			else
				cout << "N\n";
		}
		cout << "-\n";

		memset(dflevel, 0, sizeof(dflevel));
		memset(lowlink, 0, sizeof(lowlink));
		vector <pair<int, int>> ().swap(bridges);
		for(int i = 1 ; i <= n ; ++ i) {
			vector <int>().swap(g[i]);
		}
			
	}
	
}
