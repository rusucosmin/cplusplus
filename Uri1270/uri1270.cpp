#include <fstream>
#include <iomanip>
#include <vector>
#include <string.h>
#include <iostream>
#include <math.h>
#include <unordered_map>

using namespace std;

const int maxn = 1005;
const int maxc = 55;

int n;
unordered_map <string, int> mymap;
vector <pair<int, int> > p[maxn];
vector <int> g[maxn];
double dp[maxn][maxc];

inline double dst(pair<int, int> a, pair<int, int> b) {
	int smt = (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
	return sqrt(1.0 * smt);
}

inline void dfs(int node, int father) {

	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
		if(*it != father)
			dfs(*it, node);

	for(int i = 0 ; i < p[node].size() ; ++ i) {
		for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
			if(*it == father)
				continue;
			double ans = 10000000.0;
			for(int k = 0 ; k < p[*it].size() ; ++ k)
				ans = min(ans, dp[*it][k] + dst(p[node][i], p[*it][k]));
			dp[node][i] += ans;	
		}
	}
}

int main() {
	#ifndef ONLINE_JUDGE
		freopen("uri1270.in", "r", stdin);
		freopen("uri1270.out", "w", stdout);
	#endif
	while(true) {
		cin >> n;
		if (n == 0)
			return 0;

		for(int i = 0 ; i < n ; ++ i) {
			string s;
			cin >> s;
			mymap[s] = i;
			int cnt;
			cin >> cnt;
			for(int j = 0 ; j < cnt ; ++ j) {
				int x, y;
				cin >> x >> y;
				p[i].push_back(make_pair(x, y));
			}
		}
		for(int i = 1 ; i < n ; ++ i) {
			string a, b;
			cin >> a >> b;
			g[mymap[a]].push_back(mymap[b]);
			g[mymap[b]].push_back(mymap[a]);
		}
		dfs(0, 0);	
		double ans = 0x3f3f3f3f;
		for(int i = 0 ; i < p[0].size() ; ++ i)
			ans = min(ans, dp[0][i]);
		cout << fixed << setprecision(1);
		cout << ans << '\n';
		mymap.clear();
		for(int i = 0 ; i < n ; ++ i) {
			vector <int> ().swap(g[i]);
			vector <pair<int, int> > ().swap(p[i]);
		}
		memset(dp, 0, sizeof(dp));
	}
}



