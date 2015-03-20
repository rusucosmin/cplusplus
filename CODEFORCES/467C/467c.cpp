#include <fstream>
#include <iostream>

using namespace std;

const int maxn = 5005;

long long dp[maxn][maxn], sum[maxn];
int n, m, k;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("467c.in", "r", stdin);
	freopen("467c.out", "w", stdout);
	#endif

	cin >> n >> m >> k;
	for(int i = 1 ; i <= n ; ++ i) {
		int x;
		cin >> x;
		sum[i] = sum[i - 1] + x;
	}
	long long ans = 0;
	for(int i = m ; i <= n ; ++ i) {
		for(int j = 1 ; j <= k ; ++ j)
			dp[i][j] = max(dp[i - 1][j], dp[i - m][j - 1] + sum[i] - sum[i - m]);	
		ans = max(ans, dp[i][k]);
	}
	cout << ans << '\n';
	
}
