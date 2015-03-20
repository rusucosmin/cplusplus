#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 300005;

pair<int, pair<int, int> > edges[maxn];
int n, m, dp[maxn], up[maxn], ans;

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void getint(int &x) {
	x = 0;
	while(!isdigit(buff[pos])) {
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}
	while(isdigit(buff[pos])) {
		x = x * 10 + buff[pos] - '0';
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("459e.in", "r", stdin);
	freopen("459e.out", "w", stdout);
	#endif
	getint(n);
	getint(m);
	for(int i = 1 ; i <= m ; ++ i) {
		getint(edges[i].second.first);
		getint(edges[i].second.second);
		getint(edges[i].first);
	}
	sort(edges + 1, edges + m + 1);
	for(int i = 1 ; i <= m ; ) {
		int j = i;
		while(edges[i].first == edges[j + 1].first)
			++ j;
		for(int k = i ; k <= j ; ++ k)
			up[edges[k].second.second] = max(up[edges[k].second.second], dp[edges[k].second.first] + 1);
		for(int k = i ; k <= j ; ++ k)
			dp[edges[k].second.second] = max(dp[edges[k].second.second], up[edges[k].second.second]);
		i = j + 1;
	}
	for(int i = 1 ; i <= n ; ++ i)
		ans = max(ans, dp[i]);
	cout << ans << '\n';
}
