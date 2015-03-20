#include <fstream>
#include <queue>
#include <string.h>

using namespace std;

const int maxn = 50005;
const int oo = 0x3f3f3f3f;

int n, m, dp[maxn];
vector <pair<int, int> > g[maxn];

inline void dijkstra(int st) {
	priority_queue<pair<int, int> , vector <pair<int, int> >, greater<pair<int, int> > > q;
	memset(dp, oo, sizeof(dp));
	dp[st] = 0;
	q.push(make_pair(0, st));
	while(!q.empty()) {
		int node = q.top().second;
		int cost = q.top().first;
		q.pop();
		if(dp[node] < cost)
			continue;
		for(vector <pair<int, int> > :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
			if(dp[it->first] > dp[node] + it->second) {
				dp[it->first] = dp[node] + it->second;
				q.push(make_pair(dp[it->first], it->first));
			}
		}
	}
}

int main() {
	ifstream fin("dijkstra.in");
	ofstream fout("dijkstra.out");

	fin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y, z;
		fin >> x >> y >> z;
		g[x].push_back(make_pair(y, z));
	}
	dijkstra(1);
	for(int i = 2 ; i <= n ; ++ i)
		if(dp[i] == 0x3f3f3f3f)
			fout << 0 << ' ';
		else
			fout << dp[i] << ' ';
}
