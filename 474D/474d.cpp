#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const int maxn = 100005;
const int mod = 1000000007;

int t, n, k, dp[maxn], sum[maxn];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("474d.in", "r", stdin);
	freopen("474d.out", "w", stdout);
	#endif

	cin >> t >> k;

	dp[0] = 1;
	for(int i = 1 ; i < maxn ; ++ i) {
		if(i < k)
			dp[i] = 1;
		else
			dp[i] = (dp[i - 1] + dp[i - k]) % mod;
		sum[i] = (sum[i - 1] + dp[i]) % mod;
	}
	for(int i = 1 ; i <= t ; ++ i) {
		int x, y;
		cin >> x >> y;
		cout << (sum[y] - sum[x - 1] + mod) % mod<< '\n';
	}
}
