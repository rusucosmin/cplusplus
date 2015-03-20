#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

const int maxn = 21;
const int oo = 0x3f3f3f3f;

int dp[1 << maxn][maxn], n, v[maxn], a[maxn][maxn];

inline int nrbiti(int x) {
	int ret = 0;
	while(x) {
		ret += (x & 1);
		x >>= 1;
	}
	return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uri1482.in", "r", stdin);
	freopen("uri1482.out", "w", stdout);
	#endif
	while(true) {
		scanf("%d", &n);
		if(n == 0)
			return 0;
		memset(dp, oo, sizeof(dp));
		int ans = 0;
		for(int i = 0 ; i < n ; ++ i) {
			scanf("%d", &v[i]);
			dp[1 << i][i] = v[i];
			if(dp[1 << i][i] <= 420)
				ans = 1;
		}
		for(int i = 0 ; i < n ; ++ i)
			for(int j = 0 ; j < n ; ++ j)
				scanf("%d", &a[i][j]);
		if(!ans) {
			cout << "0\n";
			continue;
		}
		int aux;
		for(int conf = 1 ; conf < (1 << n) ; ++ conf)
			for(int i = 0 ; i < n ; ++ i)
				if(conf & (1 << i))
					for(int j = 0 ; j < n ; ++ j)
						if(i != j && (conf & (1 << j)) && (aux = dp[conf ^ (1 << i)][j] + a[j][i] + v[i]) <= 420) {
							dp[conf][i] = aux;
							if((aux = nrbiti(conf))> ans)
								ans = aux;
					}	
		cout << ans << '\n';
	}
}
