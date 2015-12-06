#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

const int maxn = 300005;
const int maxlg = 18;

int n, dad[maxn], anc[maxlg][maxn], dp[maxlg][maxn], maxleft[maxn], maxright[maxn], val[maxn], down[maxn], up[maxn];
int level[maxn];
vector <int> g[maxn];
int m;

inline void dfsdown(int node) {
	down[node] = 0;
	for(auto it : g[node]) {
		dfsdown(it);
		down[node] = max(down[node], max(val[it], down[it]));
	}
}

inline void dfsup(int node) {
	level[node] = level[anc[0][node]] + 1;
	if(g[node].size() == 0)
		return ;
	if(g[node].size() == 1) {
		up[g[node][0]] = max(up[node], val[node]);
		dfsup(g[node][0]);
		return ;
	}
	memset(maxleft, 0, sizeof(maxleft));
	memset(maxright, 0, sizeof(maxright));
	maxleft[0] = max(val[g[node][0]], down[g[node][0]]);

	for(int i = 1 ; i < int(g[node].size()) ; ++ i)
		maxleft[i] = max(maxleft[i - 1], max(val[g[node][i]], down[g[node][i]]));

	maxright[g[node].size() - 1] = max(val[g[node][g[node].size() - 1]], down[g[node][g[node].size() - 1]]);
	for(int i = int(g[node].size()) - 2 ; i >= 0 ; -- i)
		maxright[i] = max(maxright[i + 1], max(val[g[node][i]], down[g[node][i]]));

	up[g[node][0]] = max(max(up[node], val[node]), maxright[1]);
	dp[0][g[node][0]] = maxright[1];

	for(int i = 1 ; i + 1 < int(g[node].size()) ; ++ i) {
		up[g[node][i]] = max(maxleft[i - 1], maxright[i + 1]);
		up[g[node][i]] = max(up[g[node][i]], max(val[node], up[node]));
		dp[0][g[node][i]] = max(maxleft[i - 1], maxright[i + 1]);
	}

	up[g[node][g[node].size() - 1]] = max(maxleft[g[node].size() - 2], max(up[node], val[node]));
	dp[0][g[node][g[node].size() - 1]] = maxleft[g[node].size() - 2];

	for(auto it : g[node])
		dfsup(it);
}

ofstream fout("arbvalmax.out");

inline int query(int x, int y) {
	int diff = level[y] - level[x];
	int ans = max(down[y], up[x]);
	for(int i = 0 ; i < maxlg ; ++ i)
		if(diff & (1 << i)) {
			ans = max(ans, dp[i][y]);
			y = anc[i][y];
		}
	return ans;
}

int main() {
	ifstream fin("arbvalmax.in");

	fin >> n >> m;
	for(int i = 2 ; i <= n ; ++ i) {
		fin >> anc[0][i];
		g[anc[0][i]].push_back(i);
	}
	for(int i = 1 ; i <= n ; ++ i)
		fin >> val[i];
	dfsdown(1);
	dfsup(1);
	for(int i = 1 ; i < maxlg ; ++ i) {
		for(int j = 1 ; j <= n ; ++ j) 
			if(anc[i - 1][anc[i - 1][j]])
			{
				anc[i][j] = anc[i - 1][anc[i - 1][j]];
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][anc[i - 1][j]]);
			}
	}
	ifstream ok("arbvalmax.ok");
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		fin >> x >> y;
		int value;
		ok >> value;
		int ans = query(x, y);
		if(value != ans)
			cerr << "prostule " << ans << ' ' << value << '\n';
		fout << query(x, y) << '\n';
	}
}
