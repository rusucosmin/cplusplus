#include <fstream>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

const int maxn = 16005;

int n, m;
int arb[2][maxn << 2], euler[2][maxn];
int first[2][maxn], last[2][maxn];
int which[maxn];
int ans[maxn];
char s[maxn];
vector <int> g[maxn];

inline void dfs(int node, int ind) {
	first[ind][node] = euler[ind][0] + 1;
	for(vector <int> :: iterator it = g[node].begin(), fin = g[node].end() ; it != fin ; ++ it)
		dfs(*it, ind);
	euler[ind][ ++ euler[ind][0] ] = node;
	last[ind][node] = euler[ind][0];
}

inline void build(int node, int st, int dr, int ind) {
	if(st == dr) {
		arb[ind][node] = st;
		return;
	}
	int mid = ((st + dr) >> 1);
	build((node << 1), st, mid, ind);
	build((node << 1) | 1, mid + 1, dr, ind);
	if(arb[ind][(node << 1)] > 0)
		arb[ind][node] = arb[ind][(node << 1)];
	else
		arb[ind][node] = arb[ind][(node << 1) | 1];
}

inline int query(int node, int st, int dr, int a, int b, int ind) {
	if(a <= st && dr <= b) 
		return arb[ind][node];
	int mid = ((st + dr) >> 1);
	int ret = 0;
	if(a <= mid)
		if((ret = query((node << 1), st, mid, a, b, ind)))
			return ret;
	if(mid < b)
		if((ret = query((node << 1) | 1, mid + 1, dr, a, b, ind)))
			return ret;
	return 0;
}

inline void update(int node, int st, int dr, int pos, int ind) {
	if(st == dr) {
		arb[ind][node] = 0;
		return ;
	}
	int mid = ((st + dr) >> 1);
	if(pos <= mid)
		update(node << 1, st, mid, pos, ind);
	else
		update((node << 1) | 1, mid + 1, dr, pos, ind);
	if(arb[ind][(node << 1)] > 0)
		arb[ind][node] = arb[ind][(node << 1)];
	else
		arb[ind][node] = arb[ind][(node << 1) | 1];
}

inline void solve(int node) {
	for(vector <int> :: iterator it = g[node].begin(), fin = g[node].end() ; it != fin ; ++ it)
		solve(*it);
	int ind = -1;
	if(s[node] == 'S') {
		ind = 0;
		int pos = query(1, 1, n, first[ind][node], last[ind][node], ind);
		ans[which[node]] = euler[ind][pos];
		update(1, 1, n, pos, ind);
		update(1, 1, n, last[1 - ind][euler[ind][pos]], 1 - ind);
		return;
	}
	if(s[node] == 'D') {
		ind = 1;
		int pos = query(1, 1, n, first[ind][node], last[ind][node], ind);
		ans[which[node]] = euler[ind][pos];
		update(1, 1, n, pos, ind);
		update(1, 1, n, last[1 - ind][euler[ind][pos]], 1 - ind);
		return;	
	}
}

int main() {
	ifstream fin("omizi.in");
	ofstream fout("omizi.out");

	fin >> n >> m;
	
	for(int i = 1 ; i <= n ; ++ i) {
		int x;
		while(fin >> x && x)
			g[i].push_back(x);
	}
	
	dfs(1, 0);
	for(int i = 1 ; i <= n ; ++ i)
		reverse(g[i].begin(), g[i].end());
	dfs(1, 1);

	build(1, 1, n, 0);
	build(1, 1, n, 1);

	for (int i = 1 ; i <= m ; ++ i) {
		int x;
		fin >> x;
		fin >> s[x];
		which[x] = i;
	}
	solve(1);
	
	for(int i = 1 ; i <= m ; ++ i)
		fout << ans[i] << '\n';
}
