#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

const int maxn = 100005;

int n, m, q, game[maxn], cnt[maxn], sz[maxn], father[maxn], ans[maxn];

inline int find(int x) {
	if(father[x] != x)
		father[x] = find(father[x]);
	return father[x];
}

inline void unite(int x, int y, int ind) {
	int tx = find(x);
	int ty = find(y);
	if(tx == ty)
		return ;
	father[tx] = ty;
	sz[ty] += sz[tx];
	if(sz[ty] == cnt[game[x]]) {
		ans[game[x]] = ind;
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
	#endif
	memset(ans, -1, sizeof(ans));
	cin >> n >> m >> q;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> game[i];
		++ cnt[game[i]];
		father[i] = i;
		sz[i] = 1;
	}
	for(int i = 1 ; i <= q ; ++ i) {
		int x, y;
		cin >> x >> y;
		if(game[x] != game[y])
			continue;
		unite(x, y, i);
	}
	for(int i = 1 ; i <= m ; ++ i)
		cout << ans[i] << '\n';
}
