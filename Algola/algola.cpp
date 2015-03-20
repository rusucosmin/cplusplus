#include <fstream>
#include <cstring>
#include <vector>
#include <bitset>
#include <cassert>
#include <queue>
#include <iostream>

using namespace std;

const int maxn = 5005;
const int oo = 0x3f3f3f3f;

vector <pair<int, int> > w[55];
vector <int> g[maxn];
bitset <maxn> used;
queue <int> q;
int n, m, s, d, c[maxn][maxn], f[maxn][maxn], totalp, father[maxn], maxflow;

inline int getnode(int node, int tmp) {
	return node + (tmp - 1) * n;
}

inline bool bfs(int source, int sink) {
	used.reset();
	used[source] = 1;
	q.push(source);
	while(!q.empty()) {
		int node = q.front();
		q.pop();
		if(node == sink)
			continue;
		for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
			if(c[node][*it] - f[node][*it] > 0 && !used[*it]) {
				used[*it] = 1;
				father[*it] = node;
				q.push(*it);
			}
	}
	return used[sink];
}

inline int getmaxflow(int source, int sink) {
	while(bfs(source, sink)) {
		for(vector <int> :: iterator it = g[sink].begin() ; it != g[sink].end() ; ++ it) {
			if(!used[*it] || c[*it][sink] - f[*it][sink] <= 0)
				continue;
			father[sink] = *it;
			int bottleneck = oo;
			for(int i = sink ; i != source ; i = father[i])
				bottleneck = min(bottleneck, c[father[i]][i] - f[father[i]][i]);
			for(int i = sink ; i != source ; i = father[i]) {
				f[father[i]][i] += bottleneck;
				f[i][father[i]] -= bottleneck;
			}
			maxflow += bottleneck;
		}
	}
	return maxflow;
}

inline int solve() {
	for(int t = 1 ;  ; ++ t) {
		for(int i = 1 ; i <= n ; ++ i) {
			int x = getnode(i, t);
			int y = getnode(i, t + 1);
			g[x].push_back(y);
			g[y].push_back(x);
			c[x][y] = oo;
			for(vector <pair<int, int> > :: iterator it = w[i].begin(), fin = w[i].end() ; it != fin ; ++ it) {
				y = getnode(it->first, t + 1);
				g[x].push_back(y);
				g[y].push_back(x);
				c[x][y] = it->second;
			}
			d = getnode(1, t + 1);
		}
		if(getmaxflow(s, d) == totalp) 	
			return t;
	}
	assert(false);
}

int main() {
	ifstream fin("algola.in");
	ofstream fout("algola.out");

	fin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i) {
		int x;
		fin >> x;
		totalp += x;
		g[s].push_back(i);
		g[i].push_back(s);
		c[s][i] = x;
	}
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y, z;
		fin >> x >> y >> z;
		w[x].push_back(make_pair(y, z));
		w[y].push_back(make_pair(x, z));
	}
	fout << solve() << '\n';
}
