#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 100005;
const int maxlg = 25;

int n, m, rmq[maxlg][maxn << 1], euler[maxn << 1], lvl[maxn << 1], h, lg[maxn << 1], level[maxn], first[maxn];
vector <int> g[maxn];

inline void dfs(int node, int father) {
	level[node] = level[father] + 1;
	euler[++ h] = node;
	lvl[h] = level[node];
	first[node] = h;
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
		dfs(*it, node);
		euler[++ h] = node;
		lvl[h] = level[node];
	}
}

inline int lca(int x, int y) {
	x = first[x];
	y = first[y];
	if(x > y)
		swap(x, y);
	int l = lg[y - x + 1];
	int ans = rmq[l][x];
	if(lvl[ans] > lvl[rmq[l][y - (1 << l) + 1]])
		ans = rmq[l][y - (1 << l) + 1];
	return euler[ans];
}

int main() {
	ifstream fin("lca.in");
	ofstream fout("lca.out");
	fin >> n >> m;
	for(int i = 2 ; i <= n ; ++ i) {
		int x;
		fin >> x;
		g[x].push_back(i);
	}
	dfs(1, 0);
	for(int i = 2 ; i <= h ; ++ i)
		lg[i] = lg[i >> 1] + 1;
	///rmq
	for(int i = 1 ; i <= h ; ++ i)
		rmq[0][i] = i;
	for(int i = 1 ; (1 << i) <= h ; ++ i) {
		int aux = (1 << (i - 1));
		for(int j = 1 ; j + (1 << i) - 1 <= h ; ++ j) {
			rmq[i][j] = rmq[i - 1][j];
			if(lvl[rmq[i][j]] > lvl[rmq[i - 1][j + aux]])
				rmq[i][j] = rmq[i - 1][j + aux];
		}
	}
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		fin >> x >> y;
		fout << lca(x, y) << '\n';
	}
}
