#include <fstream>
#include <vector>
#include <string.h>
#include <iostream>

using namespace std;

const int maxn = 1005;

int n, k, m, pos[6][maxn], p[6][maxn], dp[maxn];
vector <int> g[maxn];

inline void dfs(int node) {
	dp[node] = 1;
	for(auto it : g[node]) {
		if(!dp[it])
			dfs(it);
		dp[node] = max(dp[node], 1 + dp[it]);
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("463d.in", "r", stdin);
	freopen("463d.out", "w", stdout);
	#endif
	cin >> n >> k;
	for(int i = 1 ; i <= k ; ++ i)
		for(int j = 1 ; j <= n ; ++ j) {
			cin >> p[i][j];
			pos[i][ p[i][j] ] = j;
		}
	
	for(int i = 1 ; i <= n ; ++ i) {
		for(int j = 1 ; j <= n ; ++ j) {
			if(i == j)
				continue;
			bool okay = true;
			for(int step = 1 ; step <= k ; ++ step)
				if(pos[step][i] > pos[step][j])
					okay = false;
			if(okay)
				g[i].push_back(j);
		}
	}

	for(int i = 1 ; i <= n ; ++ i)
		if (!dp[i])
			dfs(i);
	int ans = 0;
	for(int i = 1 ; i <= n ; ++ i)
		ans = max(ans, dp[i]);
	cout << ans << '\n';
	
}
