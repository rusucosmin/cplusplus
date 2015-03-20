#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

const int maxn = 2005;

int n, t, k, a[maxn], dp[maxn];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("hrknapsack.in", "r", stdin);
	freopen("hrknapsack.out", "w", stdout);
	#endif

	cin >> t;
	while(t --) {
		cin >> n >> k;
		for(int i = 0 ; i < n ; ++ i)
			cin >> a[i];
		memset(dp, 0, sizeof(dp));
		for(int i = 0 ; i <= k ; ++ i)
			for(int j = 0 ; j < n ; ++ j)
				if(i >= a[j])
					dp[i] = max(dp[i], dp[i - a[j]] + a[j]);
		cout << dp[k] << '\n';
	}	
}
