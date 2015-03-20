#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>

using namespace std;

const int maxn = 2005;

int n, a[maxn][maxn], father[maxn];
long long dp[maxn];
vector <pair<int, pair<int, int> > > edges;
vector <pair<int, int> > g[maxn];

inline void dfs(int node, int father) {
	for(vector <pair<int, int> > :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
		if(it->first != father) {
			dp[it->first] = dp[node] + it->second;
			dfs(it->first, node);
		}
}

inline void check() {
	for(int i = 1 ; i <= n ; ++ i) {
		dp[i] = 0;
		dfs(i, i);
		for(int j = 1 ; j <= n ; ++ j)
			if(dp[j] != a[i][j]) {
				cout << "NO\n";
				exit(0);
			}
	}
	cout << "YES\n";
}

inline int find(int x) {
	if(x != father[x])
		father[x] = find(father[x]);
	return father[x];
}

const int lim = (1 << 20);
int pos;
char buff[lim];

inline void getint(int &x) {
	x = 0;
	while(!isdigit(buff[pos])) {
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}
	while(isdigit(buff[pos])) {
		x = x * 10 + buff[pos] - '0';
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("472d.in", "r", stdin);
	freopen("472d.out", "w", stdout);
	#endif
	getint(n);
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= n ; ++ j) {
			getint(a[i][j]);
			if(i == j || !a[i][j])
				continue;
			edges.push_back(make_pair(a[i][j], make_pair(i, j)));
		}
	sort(edges.begin(), edges.end());
	for(int i = 1 ; i <= n ; ++ i)
		father[i] = i;
	int edgescnt = 0;
	for(int i = 0 ; i < edges.size() ; ++ i) {
		int x = edges[i].second.first;
		int y = edges[i].second.second;
		int z = edges[i].first;
		int tx = find(x);
		int ty = find(y);
		if(tx == ty)
			continue;
		++ edgescnt;
		father[tx] = ty;
		g[x].push_back(make_pair(y, z));
		g[y].push_back(make_pair(x, z));
	}
	if(edgescnt != n - 1) {
		cout << "NO\n";
		return 0;
	}
	check();
}
