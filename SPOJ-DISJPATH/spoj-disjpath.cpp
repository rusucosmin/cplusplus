#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <iostream>
#include <sstream>
#include <queue>
#include <string.h>

using namespace std;

const int maxn = 1005;
const int oo = 0x3f3f3f;

int n, k, cap[maxn][maxn], flow[maxn][maxn], father[maxn];
vector <int> g[maxn];
bitset <maxn> used;

inline void addedge(int x, int y, int c, int rc) {
	g[x].push_back(y);
	cap[x][y] = c;
	g[y].push_back(x);
	cap[y][x] = rc;
}

inline bool bfs(int source, int sink) {
	queue <int> q;
	used.reset();
	used[source] = 1;
	q.push(source);
	while(!q.empty()) {
		int node = q.front();
		q.pop();
		if(node == sink)
			continue;
		for(auto it : g[node])
			if(!used[it] && cap[node][it] - flow[node][it] > 0) {
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
		for(vector <int> :: iterator it = g[sink].begin() ; it != g[sink].end() ; ++ it) {
			if(!used[*it] || cap[*it][sink] - flow[*it][sink] <= 0)
				continue;
			father[sink] = *it;
			int bottleneck = oo;
			for(int i = sink ; i != source ; i = father[i])
				bottleneck = min(bottleneck, cap[father[i]][i] - flow[father[i]][i]);
			if(!bottleneck)
				continue;
			for(int i = sink ; i != source ; i = father[i]) {
				flow[father[i]][i] += bottleneck;
				flow[i][father[i]] -= bottleneck;
			}
			maxflow += bottleneck;
		}
	return maxflow;
}

int test;

inline bool bfs2(int source, int sink) {
	queue <int> q;
	used.reset();
	used[source] = 1;
	q.push(source);
	while(!q.empty()) {
		int node = q.front();
		q.pop();
		if(node == sink)
			continue;
		for(auto it : g[node]) {
			if(!used[it] && flow[node][it]) {
				used[it] = 1;
				father[it] = node;
				q.push(it);
			}
		}
	}
	return used[sink];
}

inline void write(int source, int sink) {
		while(bfs2(source, sink)) {
			for(auto it : g[sink]) {
				if(!k)
					return ;
				if(!used[it] || !flow[it][sink])
					continue;
				father[sink] = it;
				vector <int> v;
				for(int i = sink ; i != source ; i = father[i]) {
					v.push_back(i); 
					flow[father[i]][i] = 0;
				}
				v.push_back(1);
				for(auto i = v.rbegin() ; i != v.rend() ; ++ i)
					if(*i <= n)
						cout << *i << ' ';
				cout << '\n';
				-- k;
			}
		}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("spoj-disjpath.in", "r", stdin);
	freopen("spoj-disjpath.out", "w", stdout);
	#endif
	while(cin >> k >> n) {
		if(!k && !n)
			return 0;
		cin.get();
		for(int i = 1 ; i <= n ; ++ i) {
			string s;
			getline(cin, s);
			istringstream get(s);
			int x;
			addedge(i, i + n, 1, 0);
			while(get >> x)
				addedge(i + n, x, 1, 0);
		}
		int maxflow = getmaxflow(n + 1, 2);
		if(test != 0)
			cout << "\n";
		cout << "Case #" << ++ test << ":\n";
		if(maxflow < k)	
			cout << "Impossible\n";
		else
			write(1 + n, 2);
		for(int i = 0 ; i <= 2 * n ; ++ i)
			vector <int> ().swap(g[i]);
		memset(cap, 0, sizeof(cap));
		memset(flow, 0, sizeof(flow));
	}
}
