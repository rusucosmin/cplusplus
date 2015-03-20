#include <fstream>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <bitset>

using namespace std;

const int maxn = 200005;

int n, m, cycle, ind;
unordered_map<int, int> idx;
vector <int> g[maxn];
int used[maxn];

inline void dfs(int node, int father, int actlevel) {
	used[node] = actlevel;
	
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
		if(!used[*it])
			dfs(*it, node, actlevel + 1);
		else {
			if(*it == father)
				continue;
			cycle = max(actlevel - used[*it] + 1, used[*it] - actlevel + 1);
		}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uri1322.in", "r", stdin);
	freopen("uri1322.out", "w", stdout);
	#endif
	while (true) {
		cin >> n >> m;
		if(n + m == 0)
			return 0;
		for(int i = 1 ; i <= ind ; ++ i)
			vector <int>().swap(g[i]);
		idx.clear();
		ind = 0;
		memset(used, 0, sizeof(used));
		for(int i = 1 ; i <= m ; ++ i) {
			int x, y;
			cin >> x >> y;
			if(!idx[x])
				idx[x] = ++ ind;
			if(!idx[y])
				idx[y] = ++ ind;
			x = idx[x];
			y = idx[y];
			g[x].push_back(y);
			g[y].push_back(x);
		}
		bool ok = true;
		for(int i = 1 ; i <= ind ; ++ i) {
			sort(g[i].begin(), g[i].end());
			g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end());
			if(g[i].size() > 2)
				ok = false;
		}
		if(ok == false) {
			cout << "N\n";
			continue;
		}
		cycle = -1;
		for(int i = 1 ; i <= ind ; ++ i)
			if(!used[i])
				dfs(i, -1, 1);
		
		if(cycle == -1 || cycle == n)
			cout << "Y\n";
		else
			cout << "N\n";
	}
	

}
