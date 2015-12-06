#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <bitset>
#include <algorithm>

using namespace std;

const int maxn = 100005;

int n, cnt[maxn], dp[maxn], deg[maxn];
vector <int> g[maxn], tsort;
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
	freopen("uva-988.in", "r", stdin);
	freopen("uva-988.out", "w", stdout);
	#endif
	int test = 0;
	while(cin >> n) {
		if(test)
			cout << "\n";
		++ test;
		for(int i = 0 ; i < n ; ++ i) {
			cin >> cnt[i];
			dp[i] = 0;
			for(int j = 0 ; j < cnt[i] ; ++ j) {
				int x;
				cin >> x;
				g[i].push_back(x);
				++ deg[x];
			}
		}
		for(int i = 0 ; i < n ; ++ i)
			if(deg[i] == 0)
				dp[i] = 1;
		for(int i = 0 ; i < n ; ++ i)
			if(!used[i])
				dfs(i);
		reverse(tsort.begin(), tsort.end());
		int ans = 0;
		for(int i = 0 ; i < tsort.size() ; ++ i) {
			int node = tsort[i];
			if(!cnt[node])
				ans += dp[node];
			for(auto it : g[node])
				dp[it] += dp[node];
		}
		cout << ans << '\n';
		for(int i = 0 ; i < n ; ++ i)
			vector <int> ().swap(g[i]);
		memset(deg, 0, sizeof(deg));
		used.reset();
		vector <int> ().swap(tsort);
	}
	
}
