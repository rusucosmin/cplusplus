#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int lim = (1 << 20);
char buff[lim];
int pos;

const int maxn = 100105;

inline void getint(int &x) {
	x = 0;
	char sgn = '+';
	while(!('0' <= buff[pos] && buff[pos] <= '9')) {
		sgn = buff[pos];
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}
	while('0' <= buff[pos] && buff[pos] <= '9') {
		x = x * 10 + buff[pos] - '0';
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}
	if(sgn == '-')
		x = -x;
}

int n, k, w[maxn], euler[maxn], cnt, subarb[maxn];
long long dp[maxn];
vector <int> g[maxn];

inline void dfs(int node) {
	subarb[node] = 1;
	euler[++ cnt] = node;
	for(auto it : g[node])
		if(!subarb[it]) {
			dfs(it);
			subarb[node] += subarb[it];
		}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("hrtreepruning.in", "r", stdin);
	freopen("hrtreepruning.out", "w", stdout);
	#endif
	getint(n);
	getint(k);
	for(int i = 1 ; i <= n ; ++ i)
		getint(w[i]);
	for(int i = 1 ; i < n ; ++ i) {
		int x, y;
		getint(x);
		getint(y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(1);
	for(int i = 1 ; i <= n ; ++ i)
		dp[i] = dp[i - 1] + 1LL * w[euler[i]];
	for(int i = 1 ; i <= k ; ++ i) {
		for(int j = n ; j >= 1 ; -- j)
			dp[j + subarb[euler[j]] - 1] = max(dp[j + subarb[euler[j]] - 1], dp[j - 1]);
		for(int j = 1 ; j <= n ; ++ j)
			dp[j] = max(dp[j], dp[j - 1] + 1LL * w[euler[j]]);
	}
	cout << dp[n] << '\n';
}
