#include <iostream>
#include <vector>

using namespace std;

const int maxn = 18;

int n, m, k, a[maxn];
vector <pair<int, int> > g[maxn];
long long dp[1 << maxn][maxn];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
	#endif
	cin >> n >> m >> k;
	for(int i = 0 ; i < n ; ++ i) {
		cin >> a[i]; 
		for(int j = 0 ; j < n ; ++ j)
			if(i != j)
				g[i].push_back(make_pair(j, 0));
		dp[1 << i][i] = a[i];
	}
	for(int i = 1 ; i <= k ; ++ i) {
		int x, y, z;
		cin >> x >> y >> z;
		-- x;
		-- y;
		g[y].push_back(make_pair(x, z));
	}
	for(int conf = 1 ; conf < (1 << n) ; ++ conf) {
		for(int j = 0 ; j < n ; ++ j) {
			if(conf & (1 << j))
				for(auto it : g[j]) {
					if(conf & (1 << it.first))
						dp[conf][j] = max(dp[conf][j], dp[conf ^ (1 << j)][it.first] + it.second + a[j]);
			}
		}
	}
	long long ans = 0;
	for(int conf = 0 ; conf < (1 << n) ; ++ conf) {
		if(__builtin_popcount(conf) == m) {
			long long sum = 0;
		//	for(int j = 0 ; j < n ; ++ j)
		//		if(conf & (1 << j))
		//			sum += a[j];
			for(int j = 0 ; j < n ; ++ j)
				if(conf & (1 << j))
					ans = max(ans, sum + dp[conf][j]);
		}
	}
	cout << ans << '\n';
}
