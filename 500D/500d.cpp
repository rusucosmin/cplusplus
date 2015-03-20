#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

const int maxn = 100005;

struct edg {
	int x, y, z;
} edge[maxn];

vector <int> g[maxn];
int subtree[maxn], n, q;

inline void dfs(int node, int father) {
	subtree[node] = 1;	
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
		if(*it == father)
			continue;
		dfs(*it, node);
		subtree[node] += subtree[*it];
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("500d.in", "r", stdin);
	freopen("500d.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i < n ; ++ i) {
		cin >> edge[i].x >> edge[i].y >> edge[i].z;
		g[edge[i].x].push_back(edge[i].y);
		g[edge[i].y].push_back(edge[i].x);
	}
	dfs(1, 0);
	long long ans = 0;
	for(int i = 1 ; i < n ; ++ i) {
		if(subtree[edge[i].x] < subtree[edge[i].y])
			swap(edge[i].x, edge[i].y);
		ans += 2LL * subtree[edge[i].y] * (n - subtree[edge[i].y]) * edge[i].z;
	}
	cin >> q;
	long double aux = 3.0 / ((long double) n * (n - 1));
	cout << fixed << setprecision(10);
	for(int i = 1 ; i <= q ; ++ i) {
		int e, d;
		cin >> e >> d;
		ans -= 2LL * subtree[edge[e].y] * (n - subtree[edge[e].y]) * (edge[e].z - d);
		cout << (long double)ans * aux << '\n';
		edge[e].z = d;
	}
}
