#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>

using namespace std;

const int maxn = 2005;
const int mod = 1000000007;

int d, n, a[maxn], dp[maxn];
vector <int> g[maxn];
bitset <maxn> used;


inline void dfs(int node, int start) {
	used[node] = 1;
	dp[node] = 1;
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
		if(!used[*it] && a[start] <= a[*it] && a[*it] <= a[start] + d) {
			if(a[*it] == a[start] && *it < start)
				continue;
			dfs(*it, start);
			dp[node] = (1LL * dp[node] * (dp[*it] + 1)) % mod;
		}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("486d.in", "r", stdin);
	freopen("486d.out", "w", stdout);
	#endif
	cin >> d >> n;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> a[i];
	for(int i = 1 ; i < n ; ++ i) {
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	int ans = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		used.reset();
		memset(dp, 0, sizeof(dp));		
		dfs(i, i);
		ans = (ans + dp[i]) % mod;
	}
	cout << ans << '\n';
}
