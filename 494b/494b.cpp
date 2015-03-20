#include <iostream>
#include <vector>
#include <string.h>
#include <bitset>

using namespace std;

const int maxn = 100005;
const int MOD = 1000000007;

char s[maxn], t[maxn];
int dp[maxn], ans[maxn], sum[maxn], pi[maxn];
bitset <maxn> good;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("494b.in", "r", stdin);
	freopen("494b.out", "w", stdout);
	#endif
	cin >> s + 1 >> t + 1;
	
	int k = 0;
	int n = strlen(s + 1);
	int m = strlen(t + 1);

	for(int i = 2 ; i <= m ; ++ i) {
		while(k > 0 && t[k + 1] != t[i])
			k = pi[k];
		if(t[k + 1] == t[i])
		 	++ k;
		pi[i] = k;
	}

	k = 0;
	
	for(int i = 1 ; i <= n ; ++ i) {
		while(k > 0 && t[k + 1] != s[i])
			k = pi[k];	
		if(t[k + 1] == s[i])
			++ k;
		if(k == m)
			good[i] = true;
	}

	for(int i = 1 ; i <= n ; ++ i) {
		if(!good[i])
			dp[i] = dp[i - 1];
		else
			dp[i] = (i - m + 1 + sum[i - m]) % MOD;
		ans[i] = (ans[i - 1] + dp[i]) % MOD;
		sum[i] = (sum[i - 1] + ans[i]) % MOD;
	}
	cout << ans[n] << '\n';
}
