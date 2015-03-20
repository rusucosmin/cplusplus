#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

const int maxn = 2005;

int n, a[maxn][maxn], dp[2*maxn], ds[2*maxn];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("463c.in", "r", stdin);
	freopen("463c.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= n ; ++ j) {
			cin >> a[i][j];
			cerr << i << ' ' << j << ' ' << n + i - j << ' ' << i + j - 1 << '\n';
			dp[n + i - j] += a[i][j];
			ds[i + j - 1] += a[i][j];
		}
	for(int i = 1 ; i < n + n ; ++ i);
}
