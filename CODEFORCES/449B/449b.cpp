#include <fstream>
#include <iostream>
#include <string.h>
#include <queue>

using namespace std;

const int maxn = 100005;

struct edge {
	int type, x, cost;
	edge(int _type, int _x, int _cost) {
		type = _type;
		x = _x;
		cost = _cost;
	}
};

int n, m, k, dp[maxn], in[maxn];
vector <edge> g[maxn], newg[maxn];

inline void dijkstra(int stnode) {
	memset(dp, 0x3f3f3f3f, sizeof(dp));
	priority_queue<pair<int, int>, vector <pair<int, int> >, greater <pair<int, int> > > q;
	dp[stnode] = 0;
	q.push(make_pair(0, stnode));
	while(!q.empty()) {
		int cost = q.top().first;
		int node = q.top().second;
		q.pop();
		if(dp[node] < cost)
			continue;
		for(vector <edge> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
			if(dp[it->x] > cost + it->cost) {
				dp[it->x] = cost + it->cost;
				q.push(make_pair(dp[it->x], it->x));
			}
	}
}

int  main() {
	#ifndef ONLINE_JUDGE
	freopen("449b.in", "r", stdin);
	freopen("449b.out", "w", stdout);
	#endif
	cin >> n >> m >> k;

	vector <pair<pair<int, int>, int>  > edges[2];

	for(int i = 1 ; i <= m  ; ++ i) {
		int x, y, z;
		cin >> x >> y >> z;
		g[x].push_back(edge(0, y, z));
		g[y].push_back(edge(0, x, z));
		edges[0].push_back(make_pair(make_pair(x, y), z));	
		edges[0].push_back(make_pair(make_pair(y, x), z));
	}

	for(int i = 1 ; i <= k ; ++ i) {
		int x, z;
		cin >> x >> z;
		g[1].push_back(edge(1, x, z));
		g[x].push_back(edge(1, 1, z));
		edges[1].push_back(make_pair(make_pair(1, x), z));
	//	edges[1].push_back(make_pair(make_pair(x, 1), z));
	}

	dijkstra(1);

	for(vector <pair<pair<int, int>, int> > :: iterator it = edges[0].begin() ; it != edges[0].end() ; ++ it) {
		int x = it->first.first;
		int y = it->first.second;
		int z = it->second;
		
		if(dp[x] + z == dp[y])
			++ in[y];	
	}
	int removed = 0;
	for(vector <pair<pair<int, int>, int> > :: iterator it = edges[1].begin() ; it != edges[1].end() ; ++ it) {
		int x = it->first.first;
		int y = it->first.second;
		int z = it->second;

		if(dp[x] + z == dp[y])
			++ in[y];
		else
			++ removed;		
	}
	for(vector <pair<pair<int, int>, int> > :: iterator it = edges[1].begin() ; it != edges[1].end() ; ++ it) {
		int x = it->first.first;
		int y = it->first.second;
		int z = it->second;
		if(dp[x] + z == dp[y]) {
			if(in[y] > 1) {
				++ removed;
				-- in[y];
			}
		}
	}
	cout << removed << '\n';

}
