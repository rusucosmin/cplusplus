#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int maxn = 1005;

int dp[4][maxn][maxn], n, m, a[maxn][maxn];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("430d.in", "r", stdin);
	freopen("430d.out", "w", stdout);
	#endif
	cin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= m ; ++ j)
			cin >> a[i][j];
	
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= m ; ++ j)
			dp[0][i][j] = a[i][j] + max(dp[0][i - 1][j], dp[0][i][j - 1]);
	for(int i = n ; i >= 1 ; -- i)
		for(int j = 1 ; j <= m ; ++ j)
			dp[1][i][j] = a[i][j] + max(dp[1][i + 1][j], dp[1][i][j - 1]);
	for(int i = n ; i >= 1 ; -- i)
		for(int j = m ; j >= 1 ; -- j)
			dp[2][i][j] = a[i][j] + max(dp[2][i + 1][j], dp[2][i][j + 1]);
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = m ; j >= 1 ; -- j)
			dp[3][i][j] = a[i][j] + max(dp[3][i - 1][j], dp[3][i][j + 1]);
	
	int ans = 0;
	for(int i = 2 ; i < n ; ++ i)
		for(int j = 2 ; j < m ; ++ j) {
			ans = max(ans, dp[0][i - 1][j] + dp[2][i + 1][j] + dp[1][i][j - 1] + dp[3][i][j + 1]);
			ans = max(ans, dp[0][i][j - 1] + dp[2][i][j + 1] + dp[1][i + 1][j] + dp[3][i - 1][j]);
		}
	cout << ans << '\n';
}
