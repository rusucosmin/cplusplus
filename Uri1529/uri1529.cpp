#include <fstream>
#include <memory.h>
#include <vector>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int maxn = 12;
const int maxt = 55;
const int oo = 0x3f3f3f3f;

vector <pair<int, int> > g[maxn];
int dp[maxn][maxt], n, m, t, station[maxn];

inline int dijkstra(int source, int sink) {
	priority_queue <pair<int, pair<int, int> > , vector< pair<int, pair<int, int> > >, greater <pair<int, pair<int, int> > > > q;
	memset(dp, oo, sizeof(dp));
	dp[source][t] = 0;
	q.push(make_pair(0, make_pair(source, t)));
	while(!q.empty()) {
		int cost = q.top().first;
		int node = q.top().second.first;
		int gas = q.top().second.second;
		q.pop();

		if(dp[node][gas] < cost)
			continue;

		for(vector <pair<int, int> > :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
			if(gas - it->second >= 0) {
				int newgas = gas - it->second;
				for(int lit = 0 ; lit + newgas <= t ; ++ lit) {
					int newcost = cost + lit * station[it->first];
					if(dp[it->first][newgas + lit] > newcost) {
						dp[it->first][newgas + lit] = newcost;
						q.push(make_pair(newcost, make_pair(it->first, newgas + lit)));
					}
				}
			}
		}
	}
	int ans = oo;
	for(int i = 0 ; i <= t;  ++ i)
		ans = min(ans, dp[sink][i]);
	
	if(ans == oo)
		return -1;
	return ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uri1529.in", "r", stdin);
	freopen("uri1529.out", "w", stdout);
	#endif
	while(cin >> n >> m >> t) {
		if((n + m + t) == 0)
			return 0;
		for(int i = 1 ; i <= m ; ++ i) {
			int x, y, z;
			cin >> x >> y >> z;
			g[x].push_back(make_pair(y, z));
			g[y].push_back(make_pair(x, z));
		}
		for(int i = 1 ; i <= n ; ++ i)
			cin >> station[i];
		cout << dijkstra(1, n) << '\n';
	}
	
}
