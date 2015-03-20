#include <iostream>
#include <string.h>
#include <bitset>
#include <vector>
#include <map>
#include <queue>

using namespace std;

const int maxn = 40;

int n, m, t, source, sink;
map<string, int> _hash = { {"XXL", 1}, {"XL", 2}, {"L", 3}, {"M", 4}, {"S", 5}, {"XS", 6} };
vector <int> g[maxn * 2];
int c[maxn * 2][maxn * 2];
int father[maxn * 2];
bitset <maxn * 2> used;
queue <int> q;

int deb = 0;
inline bool bfs(int source, int sink) {
	while(!q.empty())
		q.pop();
	used.reset();
	memset(father, 0, sizeof(father));
	used[source] = 1;
	q.push(source);
	while (!q.empty()) {
		int node = q.front();
		q.pop();
		if(node == sink)
			continue;
		for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
			if(!used[*it] && c[node][*it] > 0) {
				used[*it] = 1;
				father[*it] = node;
				q.push(*it);
			}
	}
	return used[sink];
}

inline int getmaxflow(int source, int sink) {
	int maxflow = 0;
	while(bfs(source, sink)) 
		for(vector <int> :: iterator it = g[sink].begin() ; it != g[sink].end() ; ++ it) {
			if(!used[*it] || c[*it][sink] <= 0)
				continue;
			father[sink] = *it;
			int bottleneck = 0x3f3f3f3f;
			for(int i = sink ; i != source ; i = father[i]) {
				bottleneck = min(bottleneck, c[father[i]][i]);	
			}
			if(!bottleneck)
				continue;
			for(int i = sink ; i != source ; i = father[i]) {
				c[father[i]][i] -= bottleneck;
				c[i][father[i]] += bottleneck;
			}
			maxflow += bottleneck;
		}
	return maxflow;
}

int main() {
	#ifndef ONLINE_JUDGE
		freopen("uri1362.in", "r", stdin);
		freopen("uri1362.out", "w", stdout);
	#endif
	cin >> t;
	
	while (t --) {
		cin >> n >> m;
		source = 0;
		sink = m + 6 + 1;

		for(int i = 1 ; i <= m ; ++ i) {
			string x, y;
			cin >> x >> y;
			
			g[i].push_back(m + _hash[x]);
			g[m + _hash[x]].push_back(i);

			g[i].push_back(m + _hash[y]);
			g[m + _hash[y]].push_back(i);

			c[i][m + _hash[x]] = 1;
			c[i][m + _hash[y]] = 1;

			g[source].push_back(i);
			g[i].push_back(source);

			c[source][i] = 1;
		}
		for(int i = m + 1 ; i <= m + 6 ; ++ i) {
			g[i].push_back(sink);
			g[sink].push_back(i);
			c[i][sink] = n / 6;
		}
		int mf = getmaxflow(source, sink);
		if(mf == m)
			cout << "YES\n";
		else
			cout << "NO\n";
		for(int i = source ; i <= sink ; ++ i)
			vector <int> ().swap(g[i]);
		memset(c, 0, sizeof(c));
	}
}
