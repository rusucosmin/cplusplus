#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <bitset>
#include <string.h>

using namespace std;

const int maxn = 5005;
const long long oo = (1LL << 60);

int n, m;
long long dist[maxn], dist2[maxn];
bitset <maxn> inq;
vector <pair<int, long long> > g[maxn];

inline void bellmanford() {
	for(int i = 1 ; i <= n ; ++ i)
		dist[i] = dist2[i] = oo;
	queue <int> q;
	q.push(1);
	inq[1] = 0;
	dist[1] = 0;
	while(!q.empty()) {
		int node = q.front();
		q.pop();
		inq[node] = 0;
		for(vector <pair<int, long long> > :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
			if(dist[it->first] > dist[node] + it->second) {
				dist2[it->first] = dist[it->first];
				dist[it->first] = dist[node] + it->second;
				if(inq[it->first])
					continue;
				q.push(it->first);
				inq[it->first] = 1;
			}
			else if(dist2[it->first] > dist[node] + it->second && dist[it->first] < dist[node] + it->second) {
				dist2[it->first] = dist[node] + it->second;
				if(inq[it->first])
					continue;
				q.push(it->first);
				inq[it->first] = 1;
			}
			if(dist2[it->first] > dist2[node] + it->second) {
				dist2[it->first] = dist2[node] + it->second;
				if(inq[it->first])
					continue;
				inq[it->first] = 1;
				q.push(it->first);
			}
		}
	}
	cout << dist2[n] << '\n';
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("poj-3255.in", "r", stdin);
	freopen("poj-3255.out", "w", stdout);
	#endif
	cin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		long long z;
		cin >> x >> y >> z;
		g[x].push_back(make_pair(y, z));
		g[y].push_back(make_pair(x, z));
	}
	bellmanford();
}
