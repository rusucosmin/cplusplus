#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const int maxn = 100005;

int n, m, rasp;
vector <int> g[maxn];
bitset <maxn> used, cat;

void dfs(int node, int cnt) {
	if(cnt > m)
		return ;
	used[node] = 1;
	bool leaf = true;
	for(auto it : g[node]) {
		if(!used[it]) {
			if(cat[it])
				dfs(it, cnt + cat[it]);
			else
				dfs(it, 0);
			leaf = false;
		}
	}
	if(leaf)
		rasp ++ ;
}

int main() {
	#ifdef HOME
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
	#endif
	cin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i) {
		bool x;
		cin >> x;
		cat[i] = x;
	}
	for(int i = 1 ; i < n ; ++ i) {
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(1, cat[1]);
	cout << rasp << '\n';
}
