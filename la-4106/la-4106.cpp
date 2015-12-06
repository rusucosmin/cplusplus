#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

const int maxn = 2005;

int maxline[maxn], dp[maxn][maxn], g[maxn][maxn], t, xxx, h, f;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("la-4106.in", "r", stdin);
	freopen("la-4106.out", "w", stdout);
	#endif
	cin >> xxx;
	for(int test = 1 ; test <= xxx ; ++ test) {
		memset(maxline, 0, sizeof(maxline));
		memset(dp, 0, sizeof(dp));
		memset(g, 0, sizeof(g));
		cin >> t >> h >> f;
		for(int i = 1 ; i <= t ; ++ i) {
			int cnt;
			cin >> cnt;
			for(int j = 1 ; j <= cnt ; ++ j) {
				int x;
				cin >> x;
				++ g[i][x];
			}
		}
		for(int i = 1 ; i <= t ; ++ i) {
			dp[i][h] = g[i][h];	
			maxline[h] = max(maxline[h], dp[i][h]);
		}
		for(int j = h - 1 ; j >= 0 ; -- j) {
			for(int i = 1 ; i <= t ; ++ i) {
				dp[i][j] = dp[i][j + 1];
				if(j + f <= h)
					dp[i][j] = max(dp[i][j], maxline[j + f]);
				dp[i][j] += g[i][j];
				maxline[j] = max(maxline[j], dp[i][j]);
			}
		}
		cout << maxline[0] << '\n';
	}
	
}
