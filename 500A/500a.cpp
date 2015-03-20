#include <fstream>
#include <bitset>
#include <string.h>
#include <iostream>

using namespace std;

const int maxn = 100005;

bitset <maxn> used;
int n, t, a[maxn];

inline void dfs(int node) {
	used[node] = 1;
	if(node >= n)
		return ;
	dfs(node + a[node]);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("500a.in", "r", stdin);
	freopen("500a.out", "w", stdout);
	#endif
	cin >> n >> t;
	for(int i = 1 ; i < n ; ++ i)
		cin >> a[i];
	dfs(1);
	if(used[t])
		cout << "YES\n";
	else
		cout << "NO\n";
}
