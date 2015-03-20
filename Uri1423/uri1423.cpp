#include <fstream>
#include <vector>
#include <queue>
#include <iostream>
#include <string.h>

using namespace std;

const int maxn = 22;
const int maxk = 12;

int t, a, b, m, l, k, rf[maxn][maxn], dp[maxn][maxk];
vector <pair<int, int> > g[maxn];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uri1423.in", "r", stdin);
	freopen("uri1423.out", "w", stdout);
	#endif
	cin >> t;
	while (t --) {
		memset(rf, 0x3f3f3f3f, sizeof(rf));
		memset(dp, 0x3f3f3f3f, sizeof(dp));
		cin >> a >> b >> m >> l >> k;
		while (m --) {
			int x, y, z;
			cin >> x >> y >> z;
			rf[x][y] = rf[y][x] = z;
			g[x].push_back(make_pair(y, z));
			g[y].push_back(make_pair(x, z));
		}
		for(int k = 1 ; k <= a ; ++ k)
			for(int i = 1 ; i <= a + b ; ++ i)
				for(int j = 1 ; j <= a + b; ++ j)
					rf[i][j] = min(rf[i][j], rf[i][k] + rf[k][j]);
		
		priority_queue <pair<int, pair<int, int> >, vector <pair<int, pair<int, int> > > , greater <pair<int, pair<int, int> > > > q;
		dp[a + b][k] = 0;
		q.push(make_pair(0, make_pair(a + b, k)));
		while (!q.empty()) {
			int cost = q.top().first;
			int node = q.top().second.first;
			int leftk = q.top().second.second;
			q.pop();
			if(dp[node][leftk] > cost)
				continue;
			for(int i = 1 ; i <= a + b ; ++ i)
				if(rf[node][i] <= l && leftk && dp[i][leftk - 1] > dp[node][leftk]) {
					dp[i][leftk - 1] = dp[node][leftk];
					q.push(make_pair(dp[i][leftk - 1], make_pair(i, leftk - 1)));
				}	
			
			for(vector <pair<int, int> > :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
				if(dp[it->first][leftk] > dp[node][leftk] + it->second) {
					dp[it->first][leftk] = dp[node][leftk] + it->second;
					q.push(make_pair(dp[it->first][leftk], make_pair(it->first, leftk)));
				}
		}
		int ans = 0x3f3f3f3f;
		for(int i = 0 ; i <= k ; ++ i)
			ans = min(ans, dp[1][i]);
		cout << ans << '\n';
		for(int i = 1 ; i <= a + b; ++ i)
			vector <pair<int, int> > ().swap(g[i]);
 	}	
}
