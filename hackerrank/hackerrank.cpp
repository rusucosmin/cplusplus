#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

const int maxn = 40;

//// red john ia back

int dp[maxn + 5], n, t, cnt[1000000], primes;
bitset <1000000> used;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("hackerrank.in", "r", stdin);
	freopen("hackerrank.out", "w", stdout);
	#endif
	dp[0] = 1;
	for(int i = 1 ; i <= maxn ; ++ i) {
		dp[i] += dp[i - 1];
		if(i >= 4)
			dp[i] += dp[i - 4];
	}
	for(int i = 2 ; i <= dp[maxn] ; ++ i) {
		cnt[i] = primes;
		if(used[i])
			continue;
		++ primes;
		cnt[i] = primes;
		for(int j = i + i ; j <= dp[maxn] ; j += i)
			used[j] = 1;
	}
	cin >> t;
	while(t --) {
		cin >> n;
		cout << cnt[dp[n]] << '\n';
	}
	

}
