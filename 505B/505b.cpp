#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include <set>
#include <queue>

using namespace std;

const int maxn = 105;

vector <pair<int, int> > g[maxn];

int n, m, q, father[maxn];
bitset <maxn> used;

inline void dfs(int x, int y) {
	used[x] = 1;
	for(vector <pair<int, int> > :: iterator it = g[x].begin() ; it != g[x].end() ; ++ it) {
		if(it->second == y && !used[it->first]) {
			dfs(it->first, y);	
		}
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("505b.in", "r", stdin);
	freopen("505b.out", "w", stdout);
	#endif
	cin >> n >> m;
	for(int i = 0 ; i < m ; ++ i) {
		int x, y, z;
		cin >> x >> y >> z;
		g[x].push_back(make_pair(y, z));
		g[y].push_back(make_pair(x, z));
	}
	cin >> q;
	for(int i = 0 ; i < q ; ++ i) {
		int x, y;
		cin >> x >> y;
		int ans = 0;
		for(int i = 1 ; i <= m ; ++ i) {
			used.reset();
			dfs(x, i);
			if(used[y])
				++ ans;
		}
		cout << ans << '\n';
	}
	
}
