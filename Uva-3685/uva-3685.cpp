#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int maxn = 10005;
const int oo = 0x3f3f3f3f;

vector <int> g[maxn];
int n, dp[maxn][3];

inline void dfs(int node, int father) {
	dp[node][0] = 0;
	dp[node][1] = oo;
	dp[node][2] = 1;
	int sum = 0;
	for(auto it : g[node])
		if(it != father) {
			dfs(it, node);
			dp[node][0] += dp[it][1];
			dp[node][1] = min(dp[node][1], dp[it][2]);
			dp[node][2] += min(dp[it][0], dp[it][2]);
		}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uva-3685.in", "r", stdin);
	freopen("uva-3685.out", "w", stdout);
	#endif
	while(cin >> n) {
		if(n == -1)
			return 0;
		for(int i = 1 ; i < n ; ++ i) {
			int x, y;
			cin >> x >> y;
			g[x].push_back(y);
			g[y].push_back(x);
		}

		dfs(1, 0);
		cout << min(dp[1][1], dp[1][2]) << '\n';
		for(int i = 1 ; i <= n ; ++ i)
			vector <int> ().swap(g[i]);
		cin >> n;
		if(n == -1)
			return 0;
	}
}
