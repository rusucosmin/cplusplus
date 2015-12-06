#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <algorithm>

using namespace std;

const int maxn = 2005;
const int oo = 0x3f3f3f3f;

vector <int> g[maxn];
int n, dp[maxn][2];

inline void dfs(int node, int father) {
	dp[node][0] = 0;
	dp[node][1] = 1;
	for(auto it : g[node]) {
		if(it == father)
			continue;
		dfs(it, node);
		dp[node][0] = dp[node][0] + dp[it][1];
		dp[node][1] = dp[node][1] + min(dp[it][0], dp[it][1]);
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uva-10243.in", "r", stdin);
	freopen("uva-10243.out", "w", stdout);
	#endif
	while(cin >> n) {
		if(!n)
			return 0;
		for(int i = 1 ; i <= n ; ++ i) {
			int cnt;
			cin >> cnt;
			for(int j = 0 ; j < cnt ; ++ j) {
				int x;
				cin >> x;
				g[i].push_back(x);
			}
		}
		if(n == 1) {
			cout << "1\n";
		}
		else {
			dfs(1, 0);
			cout << min(dp[1][0], dp[1][1]) << "\n";
		}
		for(int i = 1 ; i <= n ; ++ i)
			vector <int> ().swap(g[i]);
	}
}
