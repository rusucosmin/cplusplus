#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int maxn = 300005;

vector <int> g[maxn];
int dist[maxn], deepest, ans[maxn], n, m, q, father[maxn];

inline void dfs(int node, int father) {
	dist[node] = dist[father] + 1;
	if(dist[deepest] < dist[node])
		deepest = node;
	for(auto it : g[node])
		if(it != father)
			dfs(it, node);
}

inline int find(int x) {
	if(father[x] != x)
		father[x] = find(father[x]);
	return father[x];
}

inline void unite(int x, int y) {
	int tx = find(x);
	int ty = find(y);
	father[tx] = ty;
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

int main (){
	#ifndef ONLINE_JUDGE
	freopen("456e.in", "r", stdin);
	freopen("456e.out", "w", stdout);
	#endif

	getint(n); getint(m); getint(q);
	for(int i = 1 ; i <= n ; ++ i)
		father[i] = i;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		getint(x); getint(y);
		g[x].push_back(y);
		g[y].push_back(x);
		unite(x, y);
	}
	dist[0] = -1;
	for(int i = 1 ; i <= n ; ++ i)
		if(find(i) == i) {
			deepest = i;
			dfs(i, 0);
			dfs(deepest, 0);
			ans[i] = dist[deepest];	
		}
	for(int i = 1 ; i <= q ; ++ i) {
		int op, x, y;
		getint(op);
		getint(x);
		if(op == 1)
			cout << ans[find(x)] << '\n';	
		else {
			getint(y);
			int tx = find(x);
			int ty = find(y);
			if(tx == ty)
				continue;
			father[tx] = ty;
			ans[ty] = max(ans[tx], max(ans[ty], (ans[tx] + 1) / 2 + (ans[ty] + 1) / 2 + 1));
		}
	}
}
