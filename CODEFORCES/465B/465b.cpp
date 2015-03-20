#include <iostream>

using namespace std;

const int maxn = 1005;

int n, dp[maxn];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("465b.in", "r", stdin);
	freopen("465b.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> dp[i];
	}
	int ans = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		if(dp[i] == 1) {
			++ ans;
			++ i;
			while(dp[i] == 1)
				++ ans, ++ i;
			++ ans;
		}
	}
	cout << max(0, ans - 1) << '\n';
}
