#include <iostream>
#include <vector>
#include <queue>
#include <bitset>
#include <string.h>
#include <map>

using namespace std;

const int maxn = 100005;
const int oo = 0x3f3f3f3f;

int dp[maxn], lg[maxn], n, m;
priority_queue <pair<int, int>, vector <pair<int, int> >, greater<pair<int, int> > > q;
vector <pair<int, int> > g[maxn];
int father[maxn];
map<pair<int, int>, int> mymap;

/// dp[node] = nr minim de muchii pe un drum de la 1->node + nr minim de muchii pe un drum de 

inline void solve() {
	memset(dp, oo, sizeof(dp));
	memset(lg, oo, sizeof(lg));

	dp[1] = 0;
	q.push(make_pair(0, 1));
	lg[1] = 0;

	while(!q.empty()) {
		int node = q.top().second;
		int cost = q.top().first;

		q.pop();

		if(dp[node] < cost)
			continue;

		for(vector <pair<int, int> > :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
			if(dp[it->first] > dp[node] + 1) {
				dp[it->first] = dp[node] + 1;
				if(it->second == 0)
					lg[it->first] = lg[node] + 1;
				else
					lg[it->first] = lg[node];
				father[it->first] = node;
				q.push(make_pair(dp[it->first], it->first));
			}
			else if(dp[it->first] == dp[node] + 1) {
				if(lg[it->first] > lg[node] + (it->second == 0)) {
					lg[it->first] = lg[node] + (it->second == 0);
					father[it->first] = node;
					q.push(make_pair(dp[it->first], it->first));
				}
			}
		}
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("507e.in", "r", stdin);
	freopen("507e.out", "w", stdout);
	#endif


	int closed = 0;

	vector <pair<pair<int, int>, int> > edges;
	cin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y, z;
		cin >> x >> y >> z;
		g[x].push_back(make_pair(y, z));
		g[y].push_back(make_pair(x, z));
		edges.push_back(make_pair(make_pair(x, y), z));
		if(z == 0)
			++ closed;
	}

	solve();

	cout << m - closed - dp[n] + lg[n] + lg[n] << '\n';

	for(int i = n ; i != 1 ; i = father[i]) { 
		mymap[make_pair(father[i], i)] = 1;
		mymap[make_pair(i, father[i])] = 1;
	}


	for(int i = 0 ; i < m ; ++ i) {
		int x = edges[i].first.first;
		int y = edges[i].first.second;
		int z = edges[i].second;
		if(z == 0) { // not working
			if(mymap[make_pair(x, y)]) /// o am pe path
				cout << x << ' ' << y << ' ' << 1 - z << '\n';
		}
		else {
			if(!mymap[make_pair(x, y)])
				cout << x << ' ' << y << ' ' << 1 - z << '\n';	
		}
	}

}
