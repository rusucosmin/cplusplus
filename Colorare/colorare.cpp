#include <iostream>
#include <bitset>

using namespace std;

const int maxn = 15;

int g[maxn], n, m, v[1<<maxn];
bitset <1<<maxn> okay, done;
long long dp[maxn][1 << maxn];


inline int lsb(int x) {
	return x & (-x);
}

inline void solve() {
	int maxconf = (1 << n);
	for(int conf = 0 ; conf < maxconf ; ++ conf) {
		okay[conf] = 1;	
		for(int i = 0 ; i < n ; ++ i)
			if(conf & (1 << i))
				if(conf & g[i])
					okay[conf] = 0;
		dp[0][conf] = okay[conf];
		if(okay[conf])
			done[conf] = 1;
	}
	for(int i = 1 ; i < n ; ++ i) {
		for(int conf = 0 ; conf < maxconf ; ++ conf) {
			if(done[conf])
				continue;
			int lg = 0;
			for(int j = 0 ; j < n ; ++ j)
				if(conf & (1 << j)) {
					v[1 << lg] = 1 << j;
					lg ++;
				}
			for(int conf2 = 1 ; conf2 < (1 << lg) ; conf2 += 2) {
				int mask = 0;
				for(int x = conf2 ; x > 0 ; x -= lsb(x)) {
					mask += v[lsb(x)];	
					if(!okay[mask])
						break;
				}
				if(okay[mask])
					dp[i][conf] += 1LL * dp[i - 1][conf ^ mask] * (i + 1);
			}
			if(dp[i][conf])
				done[conf] = 1;
		}
		if(dp[i][maxconf - 1]) {
			printf("%d %lld\n", i + 1, dp[i][maxconf-1]);
			return ;
		}
	}
}

int main() {
	freopen("colorare.in", "r", stdin);
	freopen("colorare.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 0 ; i < m ; ++ i) {
		int x, y;
		scanf("%d%d", &x, &y);
		-- x; -- y;
		g[x] |= (1 << y);
		g[y] |= (1 << x);
	}
	solve();
}
