#include <fstream>
#include <vector>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <string.h>

using namespace std;

const int maxn = 1005;
const int oo = 0x3f3f3f3f;

unordered_set<int> broken;
unordered_map<int, unordered_map<int, int> > where;
vector<pair<int, pair<int, int> > > g[maxn];
int n, m, p, dp[maxn];
priority_queue <pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;

inline int dijkstra(int source, int sink) {
	memset(dp, oo, sizeof(dp));
	dp[source] = 0;
	q.push(make_pair(0, source));
	while(!q.empty()) {
		int cost = q.top().first;
		int node = q.top().second;
		q.pop();
		if(dp[node] < cost)
			continue;
		for(vector<pair<int, pair<int, int> > > :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
			if(broken.find(it->first) == broken.end()) {
				if(dp[it->second.first] > cost + it->second.second) {
					dp[it->second.first] = cost + it->second.second;
					q.push(make_pair(dp[it->second.first], it->second.first));
				}
			}
	}
	return dp[sink];
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uri1479.in", "r", stdin);
	freopen("uri1479.out", "w", stdout);
	#endif
	while(true) {
		cin >> n >> m;
		if(n + m == 0)
			return 0;
		for(int i = 1 ; i <= m ; ++ i) {
			int x, y, z;
			cin >> x >> y >> z;
			g[x].push_back(make_pair(i, make_pair(y, z)));
			where[x][y] = i;
		}
		cin >> p; 
		for(int i = 1 ; i <= p ; ++ i) {
			char s;
			int x, y, z;
			cin >> s;
			if(s == 'R') {
				cin >> x >> y;
				broken.insert(where[x][y]);
			}
			else if(s == 'I') {
				cin >> x >> y >> z;
				g[x].push_back(make_pair(++m, make_pair(y, z)));
				where[x][y] = m;	
			}
			else {
				cin >> x;
				cout << dijkstra(1, x) << '\n';
			}
		}
		for(int i = 1 ; i <= n ; ++ i) {
			vector <pair<int, pair<int, int> > > ().swap(g[i]);
			where[i].clear();
		}
		broken.clear();
		cout << '\n';
	}
	
}
