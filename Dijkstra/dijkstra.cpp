#include <fstream>
#include <queue>
#include <string.h>
#include <vector>

using namespace std;

ifstream fin("dijkstra.in");
ofstream fout("dijkstra.out");

const int maxn = 50005;
const int oo = 0x3f3f3f3f;

int n, m, dist[maxn];
vector <pair<int, int> > g[maxn];

inline void dijkstra(int stnode) {
	priority_queue <pair<int, int> > q;
	memset(dist, oo, sizeof(dist));
	dist[stnode] = 0;
	q.push(make_pair(0, stnode));
	while(!q.empty()) {
		int cost = -q.top().first;
		int node = q.top().second;
		q.pop();
		if(dist[node] != cost)
			continue;
		for(auto it : g[node]) {
			if(dist[it.first] > cost + it.second) {
				dist[it.first] = cost + it.second;
				q.push(make_pair(-dist[it.first], it.first));
			}
		}
	}
	for(int i = 2 ; i <= n ; ++ i) {
		if(dist[i] == oo)
			dist[i] = 0;
		fout << dist[i] << ' ';
	}
}

int main() {
	fin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y, z;
		fin >> x >> y >> z;
		g[x].push_back(make_pair(y, z));
	}
	dijkstra(1);
	
}
