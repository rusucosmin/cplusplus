#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <vector>
#include <bitset>
#include <cassert>

using namespace std;

const int maxn = 1005;

vector <int> g[maxn], tsort;
int n, s, dist[maxn];
bitset <maxn> used;

inline void dfs(int node) {
	used[node] = 1;
	for(auto it : g[node])
		if(!used[it])
			dfs(it);
	tsort.push_back(node);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uva-10000.in", "r", stdin);
	freopen("uva-10000.out", "w", stdout);
	#endif
	bool test = false;
	int tests = 0;
	while(cin >> n) {
		if(n == 0)
			break;
		memset(dist, 0, sizeof(dist));
		test = true;	
		cin >> s;
		int x, y;
		while(cin >> x >> y) {
			if(x == 0 && y == 0)
				break;
			g[x].push_back(y);
		}
		dfs(s);
		reverse(tsort.begin(), tsort.end());
	//	assert(tsort[0] == s);
		int ans = s;
		for(int i = 0 ; i < tsort.size() ; ++ i) {
			int node = tsort[i];
			if(dist[node] > dist[ans] || (dist[node] == dist[ans] && ans > node))
				ans = node;
			for(auto it : g[node])
				dist[it] = max(dist[it], dist[node] + 1);
		}
		cout << "Case " << ++ tests << ": The longest path from " << s << " has length " << dist[ans] << ", finishing at "
		 << ans << ".\n";
		cout << '\n';
		used.reset();
		for(int i = 1 ; i <= n ; ++ i)
			vector <int> ().swap(g[i]);
		vector <int>().swap(tsort);
	}
}
