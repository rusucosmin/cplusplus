#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>
#include <queue>

using namespace std;

ifstream fin("maxflow.in");
ofstream fout("maxflow.out");

const int maxn = 1005;
const int oo = 0x3f3f3f3f;

int n, m, cap[maxn][maxn], father[maxn];
vector <int> g[maxn];
bitset <maxn> used;
queue <int> q;

inline bool bfs(int source, int sink) {
	used.reset();
	q.push(source);
	used[source] = 1;
	while(!q.empty()) {
		int node = q.front();
		q.pop();
		if(node == sink)
			continue;
		for(auto it : g[node])
			if(!used[it] && cap[node][it] > 0) {
				used[it] = 1;
				father[it] = node;
				q.push(it);
			}
	}
	return used[sink];
}

inline int getmaxflow(int source, int sink) {
	int maxflow = 0;
	while(bfs(source, sink))
		for(auto it : g[sink]) {
			if(!used[it] || cap[it][sink] <= 0)
				continue;
			father[sink] = it;
			int bottleneck = oo;
			for(int i = sink ; i != source ; i = father[i])
				bottleneck = min(bottleneck, cap[father[i]][i]);
			if(!bottleneck)
				continue;
			for(int i = sink ; i != source ; i = father[i]) {
				cap[father[i]][i] -= bottleneck;
				cap[i][father[i]] += bottleneck;
			}
			maxflow += bottleneck;
		}
	return maxflow;
}

int main() {
	fin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y, c;
		fin >> x >> y >> c;
		cap[x][y] += c;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	fout << getmaxflow(1, n) << '\n';
}
