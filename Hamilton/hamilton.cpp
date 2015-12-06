#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

const int maxn = 18;
const int oo = 0x3f3f3f3f;

int dp[1 << maxn][maxn], n, m;
vector <pair<int, int> > g[maxn];

int main() {
	ifstream fin("hamilton.in");
	ofstream fout("hamilton.out");
	fin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y, z;
		fin >> x >> y >> z;
		g[y].push_back(make_pair(x, z));
	}
	memset(dp, oo, sizeof(dp));
	dp[1][0] = 0;
	for(int conf = 1 ; conf < (1 << n) ; ++ conf)
		for(int i = 0 ; i < n ; ++ i)
			if(conf & (1 << i))
				for(auto it : g[i])
					if(conf & (1 << it.first))
						dp[conf][i] = min(dp[conf][i], dp[conf ^ (1 << i)][it.first] + it.second);
	int ans = oo;
	for(auto it : g[0])
		ans = min(ans, dp[(1 << n) - 1][it.first] + it.second);
	if(ans == oo)
		fout << "Nu exista solutie\n";
	else
		fout << ans << '\n';
}
