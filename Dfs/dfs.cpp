#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const int maxn = 100005;

vector <int> g[maxn];
bitset <maxn> used;
int n, m, cnt;

ifstream fin("dfs.in");
ofstream fout("dfs.out");

inline void dfs(int node) {
	used[node] = 1;
	for(auto it : g[node])
		if(!used[it])
			dfs(it);
}

int main() {
	fin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		fin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	for(int i = 1 ; i <= n ; ++ i)
		if(!used[i]) {
			++ cnt;
			dfs(i);
		}
	fout << cnt << '\n';
}
