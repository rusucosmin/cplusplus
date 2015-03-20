#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 100005;

int dp[maxn], n;
vector <int> g[maxn];

inline void dfs(int node, int father, int &deepest) {
	dp[node] = dp[father] + 1;
	if(dp[deepest] < dp[node])
		deepest = node;
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
		if(*it != father)
			dfs(*it, node, deepest);
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
	int deepest = 1;
	dfs(1, 0, deepest);
	dfs(deepest, 0, deepest);
	fout << dp[deepest] << '\n';
}
