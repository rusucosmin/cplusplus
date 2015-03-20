#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <queue>

using namespace std;

const int maxn = 1005;

int n, m, c[maxn][maxn], father[maxn];
vector <int> g[maxn];

queue <int> q;
bitset <maxn> used;

inline bool bfs(int s, int d) {
	used.reset();
	q.push(s);
	used[s] = 1;
	while(!q.empty()) {
		int node = q.front();
		q.pop();
		if(node == d)
			continue;
		for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
			if(!used[*it] && c[node][*it] > 0) {
				used[*it] = 1;
				father[*it] = node;
				q.push(*it);
			}
		}
	}
	return used[d];
}

inline int getmaxflow(int s, int d) {
	int maxflow = 0;
	while(bfs(s, d)) {
		for(vector <int> :: iterator it = g[d].begin(); it != g[d].end() ; ++ it) {
			if(c[*it][d] <= 0 || !used[*it])
				continue;
			father[d] = *it;
			int bottleneck = 0x3f3f3f3f;
			for(int i = d ; i != s ; i = father[i])
				bottleneck = min(bottleneck, c[father[i]][i]);
			if(!bottleneck)
				continue;
			maxflow += bottleneck;
			for(int i = d ; i != s ; i = father[i]) {
				c[father[i]][i] -= bottleneck;
				c[i][father[i]] += bottleneck;
			}
		}
	}
	return maxflow;
}

int main() {
	ifstream fin("maxflow.in");
	ofstream fout("maxflow.out");

	fin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y, z;
		fin >> x >> y >> z;
		g[x].push_back(y);
		g[y].push_back(x);
		c[x][y] = z;
	}
	fout << getmaxflow(1, n) << '\n';
}
