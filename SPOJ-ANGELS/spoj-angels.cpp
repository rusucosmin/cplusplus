#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <string.h>

using namespace std;

const int maxn = 305;

char s[maxn][maxn];
int n, m, t, a[maxn][maxn], b[maxn][maxn], cnt1, cnt2, match[(maxn * maxn)], pereche[(maxn * maxn)];
vector <int> g[(maxn * maxn)];
bitset <(maxn * maxn)> used;

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

inline int getmaxmatching() {
	int matching = 0;
	for(bool change = true ; change ;) {
		change = false;
		used.reset();
		for(int i = 1 ; i <= cnt1 ; ++ i)
			if(!match[i] && pairup(i)) {
				change = true;
				++ matching;
			}
	}
	return matching;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("spoj-angels.in", "r", stdin);
	freopen("spoj-angels.out", "w", stdout);
	#endif
	cin.sync_with_stdio(false);
	cin >> t;
	while(t -- ) {
		cnt1 = cnt2 = 0;
		cin >> n >> m;
		for(int i = 1 ; i <= n ; ++ i)
			for(int j = 1 ; j <= m ; ++ j) {
				cin >> s[i][j];
				if(s[i][j] != 'A') {
					if(i == 1 || s[i - 1][j] == 'A')
						b[i][j] = ++ cnt2;
					else
						b[i][j] = b[i - 1][j];
					if(j == 1 || s[i][j - 1] == 'A')
						a[i][j] = ++ cnt1;
					else
						a[i][j] = a[i][j - 1];
					if(s[i][j] == 'H')
						g[a[i][j]].push_back(b[i][j]);
				}
			}
		cout << getmaxmatching() << '\n';
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		memset(match, 0, sizeof(match));
		memset(pereche, 0, sizeof(pereche));
		for(int i = 1 ; i <= cnt1 ; ++ i)
			vector <int> ().swap(g[i]);
	}
	return 0;
}
