#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const int maxn = 100005;

int n, m, comp;
vector <int> g[maxn];
bitset <maxn> used;

inline void dfs(int node) {
	used[node] = 1;
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
		if(!used[*it])
			dfs(*it);
}

int main() {
	ifstream fin("dfs.in");
	ofstream fout("dfs.out");

	fin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		fin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	for(int i = 1 ; i <= n ; ++ i)
		if(!used[i]) {
			++ comp;
			dfs(i);
		}
	fout << comp << '\n';
}
