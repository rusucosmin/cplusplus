#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int maxn = 100005;

vector <int> g[maxn];
int n, dist[maxn], deepest;

inline void dfs(int node, int father) {
	dist[node] = dist[father] + 1;
	if(dist[deepest] < dist[node])	
		deepest = node;
	for(auto it : g[node]) {
		if(it == father)
			continue;
		dfs(it, node);
	}
}

int main() {
	ifstream fin("darb.in");
	ofstream fout("darb.out");
	fin >> n;
	for(int i = 1 ; i < n ; ++ i) {
		int x, y;
		fin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	deepest = 1;
	dfs(1, 0);
	dfs(deepest, 0);
	fout << dist[deepest] << '\n';
}
