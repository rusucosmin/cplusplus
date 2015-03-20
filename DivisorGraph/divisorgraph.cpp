#include <fstream>
#include <bitset>
#include <vector>

using namespace std;

const int maxn = 5005;
const int mod = 1000000007;

vector <int> g[maxn], tsort;
int n, m, dp[maxn];
bitset <maxn> used;

inline void dfs(int node) {
	used[node] = 1;
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
		if(!used[*it])
			dfs(*it);
	tsort.push_back(node);
}

int main () {
	ifstream fin("divisorgraph.in");
	ofstream fout("divisorgraph.out");

	int t;
	fin >> t;
	while( t -- ) {
	fin >> n >> m;
	while (m -- ) {
		int x, y;
		fin >> x >> y;
		g[x].push_back(y);
	}
	for(int i = 1 ; i <= n ; ++ i)
		if(!used[i])
			dfs(i);
		int ans = 0;
		for(vector <int> :: reverse_iterator it = tsort.rbegin() ; it != tsort.rend() ; ++ it) {
			if(it == tsort.rbegin()) {
				dp[*it] = 1;
				ans = 1;
			}
			for(int j = 0 ; j < g[*it].size() ; ++ j) {
				int node = g[*it][j];
			//	fout << *it << ' ' << node << '\n';
				dp[node] = (1ll * dp[*it] * (j + 2)) % mod;
			}
			ans = dp[*it];
		}
		fout << ans << '\n';
	}

}
