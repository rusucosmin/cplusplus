#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <string.h>

using namespace std;

const int maxn = 150;

vector <int> g[maxn];
int n, m, t, match[maxn], pereche[maxn];
bitset <maxn> used;

inline bool pairup(int node) {
	if(used[node])
		return 0;
	used[node] = 1;
	for(auto it : g[node])
		if(!pereche[it] || pairup(pereche[it])) {
			pereche[it] = node;
			match[node] = it;
			return 1;
		}
	return 0;
}

inline int maxmatching() {
	memset(match, 0, sizeof(match));
	memset(pereche, 0, sizeof(pereche));
	int ret = 0;
	for(bool change = true ; change ; ) {
		change = false;
		used.reset();
		for(int i = 1 ; i <= n ; ++ i)
			if(!match[i] && pairup(i)) {
				change = true;
				++ ret;
			}
	}
	return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("la-2696.in", "r", stdin);
	freopen("la-2696.out", "w", stdout);
	#endif
	cin >> t;
	while(t --) {
		cin >> n >> m;
		for(int i = 1 ; i <= m ; ++ i) {
			int x, y;
			cin >> x >> y;
			g[x].push_back(y);
		}
		cout << n - maxmatching() << '\n';
		for(int i = 1 ; i <= n ; ++ i)
			vector <int> ().swap(g[i]);
	}
}
