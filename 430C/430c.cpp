#include <iostream>
#include <vector>

using namespace std;

const int maxn = 100005;

int n, level[maxn];
bool a[maxn], b[maxn], h[maxn];
vector <int> g[maxn], ans;

inline void dfs(int node, int father) {
	level[node] = level[father] + 1;
	bool changed = 0;
	if((a[node] ^ h[level[node] % 2]) != b[node]) {
		changed = true;	
		h[level[node] % 2] ^= 1;
		ans.push_back(node);
	}
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
		if(*it == father)
			continue;
		dfs(*it, node);
	}
	if(changed)
		h[level[node] % 2] ^= 1;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("430c.in", "r", stdin);
	freopen("430c.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i < n ; ++ i) {
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	h[0] = h[1] = 0;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> a[i];
	for(int i = 1 ; i <= n ; ++ i)
		cin >> b[i];
	dfs(1, 0);
	cout << ans.size() << '\n';
	for(int i = 0 ; i < ans.size() ; ++ i)
		cout << ans[i] << '\n';
}
