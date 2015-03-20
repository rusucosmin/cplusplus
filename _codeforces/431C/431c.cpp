#include <fstream>
#include <iostream>

using namespace std;

const int maxn = 105;
const int mod = 1000000007;

int n, k, d, dp[maxn][2];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("431c.in", "r", stdin);
	freopen("431c.out", "w", stdout);
	#endif
	cin >> n >> k >> d;

	dp[0][0] = 1;
	for(int i = 1 ; i <= n ; ++ i) {
		int aux = 0;
		for(int j = i ; j >= i - min(d - 1, i) ; -- j) {
			dp[i][0] = (dp[i][0] + dp[j][0]) % mod;
			aux = (aux + dp[j][1]) % mod;
		}
		if(i < d)
			continue;
		dp[i][1] = aux;
		for(int j = i - d ; j >= i - min(k, i) ; -- j)
			dp[i][1] = (1LL * dp[i][1] + 1LL * dp[j][0] + 1LL * dp[j][1]) % mod;
	}
	cout << dp[n][1] << '\n';	
}
