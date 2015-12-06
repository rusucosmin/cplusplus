#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <bitset>

using namespace std;

const int maxn = 1005;

int t, n, m, cnt;
long long dp[maxn][maxn];
bitset <maxn> used[maxn];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uva-825.in", "r", stdin);
	freopen("uva-825.out", "w", stdout);
	#endif
	cin >> t;
	while(t -- ) {
		cin >> n >> m;
		memset(dp, 0, sizeof(dp));
		
		for(int i = 1 ; i <= n ; ++ i)
			for(int j = 1 ; j <= m ; ++ j)
				if(i == 1 && j == 1)
					dp[i][j] = 1;
				else
					if(!used[i][j])
						dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		cout << dp[n][m] << '\n';
		for(int i = 1 ; i <= n ; ++ i)
			used[i].reset();
	}
}
