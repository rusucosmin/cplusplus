#include <iostream>
#include <algorithm>
#include <bitset>
#include <vector>

using namespace std;

const int maxn = 305;

char a[maxn][maxn];
int n, p[maxn], ans[maxn];
vector<int> ind, per;
bitset <maxn> used;

inline void dfs(int node) {
	used[node] = 1;	
	ind.push_back(node);
	per.push_back(p[node]);
	for(int i = 1 ; i <= n ; ++ i)
		if(a[node][i] == '1' && !used[i])
			dfs(i);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("500b.in", "r", stdin);
	freopen("500b.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> p[i];
	for(int i = 1 ; i <= n ; ++ i)
		cin >> a[i] + 1;
	for(int i = 1 ; i <= n ; ++ i) {
		if(used[i])
			continue;
		ind.clear();
		per.clear();
		dfs(i);
		sort(ind.begin(), ind.end());
		sort(per.begin(), per.end());
		for(int j = 0 ; j < ind.size() ; ++ j)
			ans[ind[j]] = per[j];
	}
	for(int i = 1 ; i <= n ; ++ i)
		cout << ans[i] << ' ';
}
