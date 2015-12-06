#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;

const int maxn = 12;
const int maxd = 32;
const int maxk = 1005;
const int oo = 0x3f3f3f3f;

int dist[maxn][maxn][maxd], per[maxn][maxn], n, k, dp[maxn][maxk];

inline int dijkstra() {
	memset(dp, oo, sizeof(dp));
	priority_queue <pair<int, pair<int, int> > > q;
	dp[1][0] = 0;
	q.push(make_pair(0, make_pair(1, 0)));
	while(!q.empty()) {
		int cost = -q.top().first;
		int node = q.top().second.first;
		int day = q.top().second.second;
		q.pop();
		if(dp[node][day] != cost)
			continue;
		if(node == n && day == k)
			return cost;
		for(int i = 1 ; i <= n ; ++ i) {
			if(node == i)
				continue;
			if(dist[node][i][day % per[node][i]] && 
			dp[i][day + 1] > cost + dist[node][i][day % per[node][i]]) {
				dp[i][day + 1] = cost + dist[node][i][day % per[node][i]];
				q.push(make_pair(-dp[i][day + 1], make_pair(i, day + 1)));
			}
		}
	}
	return -1;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uva-590.in", "r", stdin);
	freopen("uva-590.out", "w", stdout);
	#endif
	int testcnt = 0;
	while(cin >> n >> k) {
		if(!n && !k)
			return 0;
		for(int i = 1 ; i <= n ; ++ i)
			for(int j = 1 ; j <= n ; ++ j) {
				if(i == j)
					continue;
				cin >> per[i][j];
				for(int k = 0 ; k < per[i][j] ; ++ k)
					cin >> dist[i][j][k];
			}
		int ans = dijkstra();
		cout << "Scenario #" << ++ testcnt << "\n";
		if(ans == -1)
			cout << "No flight possible.\n";
		else
			cout << "The best flight costs " << ans << ".\n";
		cout << '\n';
	}
}
