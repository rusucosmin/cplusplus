#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>

using namespace std;

const int maxn = 19;

bitset <maxn> g[maxn];
long long dp[1 << maxn][maxn];
int n, m;

inline long long memo(int conf, int node, int start, int level) {
	long long &ret = dp[conf][node];
	if(ret != -1)
		return ret;
	ret = 0;
	if(level > 2 && g[node][start])
		++ ret;
	for(int i = start ; i < n ; ++ i)
		if(!(conf & (1 << i)) && g[node][i])
			ret += memo(conf | (1 << i), i, start, level + 1);	
	return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("11d.in", "r", stdin);
	freopen("11d.out", "w", stdout);
	#endif
	cin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		cin >> x >> y;
		-- x; -- y;
		g[x][y] = g[y][x] = 1;
	}
	long long ans = 0; 
	for(int i = 0 ; i < n ; ++ i) {
		memset(dp, -1, sizeof(dp));
		ans += memo(1 << i, i, i, 1);
	}
	cout << (ans >> 1) << '\n';
}
