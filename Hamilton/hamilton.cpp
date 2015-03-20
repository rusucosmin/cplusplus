#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

const int maxn = 18;
const int oo = 0x3f3f3f3f;

int n, m, dp[1 << maxn][maxn];
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
	int maxconf = (1 << n);
	for(int conf = 1 ; conf < maxconf ; ++ conf)
		for(int i = 0 ; i < n ; ++ i)
			if(conf & (1 << i))
				for(vector <pair<int, int> > :: iterator it = g[i].begin() ; it != g[i].end() ; ++ it)
					if(conf & (1 << it->first))
						dp[conf][i] = min(dp[conf ^ (1 << i)][it->first] + it->second, dp[conf][i]);
	int ans = 0x3f3f3f3f;
	for(vector <pair<int, int> > :: iterator it = g[0].begin() ; it != g[0].end() ; ++ it)
		ans = min(ans, dp[maxconf - 1][it->first] + it->second);
	if(ans == 0x3f3f3f3f)
		fout << "Nu exista solutie\n";
	else
		fout << ans << '\n';
}
