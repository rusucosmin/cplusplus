#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <bitset>

using namespace std;

const int maxn = 205;

int n, m, match[maxn], pereche[maxn], a[maxn];
vector <int> g[maxn];
bitset <maxn> used, sl, sr;

inline bool pairup(int node){
	if(used[node])
		return 0;
	used[node] = 1;
	for(auto it : g[node]) {
		if(!pereche[it] || pairup(pereche[it])) {
			pereche[it] = node;
			match[node] = it;
			return 1;
		}
	}
	return 0;
}

inline void support(int node) {
	for(auto it : g[node])
		if(!sr[it]) {
			sr[it] = 1;
			sl[pereche[it]] = 0;
			support(pereche[it]);
		}
}

inline void maxmatching() {
	int ans = 0;
	for(bool change = true ; change ; ) {
		change = false;
		used.reset();
		for(int i = 1 ; i <= n ; ++ i)
			if(!match[i] && pairup(i)) {
				++ ans;
				change = true;
			}
	}
	cout << n - ans << '\n';
	for(int i = 1 ; i <= n ; ++ i)
		if(match[i])
			sl[i] = 1;
	for(int i = 1 ; i <= n ; ++ i) {
		if(!match[i])
			support(i);
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("spoj-divrel.in", "r", stdin);
	freopen("spoj-divrel.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> a[i];
	sort(a + 1, a + n + 1);
	n = unique(a + 1, a + n + 1) - (a + 1);
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = i + 1 ; j <= n ; ++ j) {
			if(a[j] % a[i] == 0)
				g[i].push_back(j);
		}
	maxmatching();
	for(int i = 1 ; i <= n ; ++ i)
		if(!sl[i] && !sr[i])
			cout << a[i] << ' ';
}
