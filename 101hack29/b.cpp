#include <iostream>
#include <string.h>
#include <bitset>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 500005;

int t, n, dp[maxn][2];
vector <int> g[maxn];
bitset <maxn> light;

/// dp[i][0] = nr minim de light-uri necesare astfel incat
///                tot arborele lui i sa fie corect si i nu est luminat 
/// dp[i][1] = idem dar i este luminat

const int inf = 0x3f3f3f3f;

void dfs(int node, int dad) {
	if(!light[node])
		++ dp[node][1];	
	for(auto it : g[node]) {
		if(it == dad)
			continue;
		dfs(it, node);
		if(light[node]) {
			dp[node][1] += min(dp[it][0], dp[it][1]);
			dp[node][0] = inf;
		}
		else {
			dp[node][1] += min(dp[it][0], dp[it][1]);
			dp[node][0] += dp[it][1];
		}
	}
}

int main() {
	#ifdef HOME
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
	#endif

	cin >> t;
	while(t -- ) {
		cin >> n;
		for(int i = 1 ; i <= n ; ++ i)  {
			bool x;
			cin >> x;
			light[i] = x;
		}
		for(int i = 1 ; i < n ; ++ i) {
			int x, y;
			cin >> x >> y;
			g[x].push_back(y);
			g[y].push_back(x);
		}
		dfs(1, 0);
		if(light[1])
			cout << dp[1][1] << '\n';
		else
			cout << min(dp[1][0], dp[1][1]) << '\n';
		for(int i = 1 ; i <= n ; ++ i) {
			vector <int> ().swap(g[i]);
		}
		memset(dp, 0, sizeof(dp));
	}
}
