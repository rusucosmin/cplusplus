#include <fstream>
#include <vector>
#include <string.h>
#include <iostream>
#include <queue>
#include <map>

using namespace std;

const int maxn = 10005;
const int oo = 0x3f3f3f3f;

map<int, int> dp;

inline int inverted(int x) {
	int ret = 0;
	while(x) {
		ret = ret * 10 + x % 10;
		x /= 10;
	}
	return ret;
}

inline int dijkstra(int a, int b) {
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;	
	dp.clear();
	dp[a] = 1;
	q.push(make_pair(1, a));
	while(!q.empty()) {
		int node = q.top().second;
		int cost = q.top().first;
		q.pop();
		
		if(dp[node] < cost)
			continue;
		
		if(node == b)
			return cost - 1;

		if(dp[node + 1] > cost + 1 || dp[node + 1] == 0) {
			dp[node + 1] = cost + 1;
			q.push(make_pair(cost + 1, node + 1));
		}
		int newnode=inverted(node);
		if(dp[newnode] > cost + 1 || dp[newnode] == 0) {
			dp[newnode] = cost + 1;
			q.push(make_pair(cost + 1, newnode));
		}
	}
	return -1;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uri1550.in", "r", stdin);
	freopen("uri1550.out", "w", stdout);
	#endif
	int t;
	cin >> t;
	for(int i = 1 ; i <= t; ++ i) {
		int a, b;
		cin >> a >> b;
		cout << dijkstra(a, b) << '\n';
	}
}
