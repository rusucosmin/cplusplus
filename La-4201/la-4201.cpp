#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <queue>

using namespace std;

const int maxn = 15;
const int maxmask = (1 << maxn);

int t, n, m, q, dp[maxmask];
vector <int> edges;

inline void bfs() {
	memset(dp, -1, sizeof(dp));
	queue <int> q;
	dp[0] = 0;
	q.push(0);
	while(!q.empty()) {
		int node = q.front();
		q.pop();
		for(auto it : edges) {
			int nxt = node ^ it;
			if(dp[nxt] == -1) {
				dp[nxt] = dp[node] + 1;
				q.push(nxt);
			}
		}
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("la-4201.in", "r", stdin);
	freopen("la-4201.out", "w", stdout);
	#endif
	cin.sync_with_stdio(false);
	cin >> t;
	for(int test = 1 ; test <= t ; ++ test) {
		cin >> n >> m;
		for(int i = 1 ; i <= m ; ++ i) {
			int cnt;
			cin >> cnt;
			int mask = 0;
			for(int j = 1 ; j <= cnt ; ++ j) {
				int x;
				cin >> x;
				mask |= (1 << x);
			}
			edges.push_back(mask);
		}
		bfs();
		cin >> q;
		cout << "Case " << test << ":\n";
		for(int i = 1 ; i <= q ; ++ i) {
			string s; int state = 0;
			cin >> s;
			for(int j = 0 ; j < s.size() ; ++ j)
				state = state * 2 + s[j] - '0';

			cout << dp[state] << '\n';
		}
		cout << "\n";
		edges.clear();
	}
}
