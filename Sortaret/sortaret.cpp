#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <queue>

using namespace std;

ifstream fin("sortaret.in");
ofstream fout("sortaret.out");

const int maxn = 100005;

vector <int> g[maxn], tsort;
bitset <maxn> used;
int n, m, deg[maxn];

inline void dfs(int node) {
	used[node] = 1;
	for(auto it : g[node])
		if(!used[it])
			dfs(it);
	tsort.push_back(node);
}

int main() {
	fin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		fin >> x >> y;
		g[x].push_back(y);
		++ deg[y];
	}
	queue <int> q;
	for(int i = 1 ; i <= n ; ++ i)
		if(deg[i] == 0)
			q.push(i);
	while(!q.empty()) {
		int node = q.front();
		tsort.push_back(node);
		q.pop();
		for(auto it : g[node]) {
			-- deg[it];
			if(deg[it] == 0)
				q.push(it);
		}
	}
	for(auto it : tsort)
		fout << it << ' ';
	return 0;
	for(int i = 1 ; i <= n ; ++ i)
		if(!used[i])	
			dfs(i);
	reverse(tsort.begin(), tsort.end());
	for(auto it : tsort)
		fout << it << ' ';
}
