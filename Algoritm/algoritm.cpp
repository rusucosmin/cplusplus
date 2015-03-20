#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;

ifstream fin("algoritm.in");
ofstream fout("algoritm.out");

const int maxn = 100005;
const int oo = 0x3f3f3f3f;

struct edge {
	int x, y, ind;
	edge(int _x, int _y, int _ind) {
		x = _x;
		y = _y;
		ind = _ind;
	}
};

int t, n, m, dp[maxn], dad[maxn];
vector <edge> g[maxn], gt[maxn];
vector <int> dag[maxn * 2];
vector <int> tsort;
bitset <2*maxn> used;

inline void get(int &x) {
	fin >> x;	
}

inline void dijkstra() {
	priority_queue <pair<int, int> > q;
	memset(dp, oo, sizeof(dp));
	dp[1] = 0;
	q.push(make_pair(0, 1));
	while(!q.empty()) {
		int node = q.top().second;
		int cost = -q.top().first;
		q.pop();
		if(dp[node] < cost)
			continue;
		for(vector <edge> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
			if(dp[it->x] > cost + it->y) {
				dp[it->x] = cost + it->y;
				dad[it->x] = it->ind;
				q.push(make_pair(-dp[it->x], it->x));
			}
	}
}

inline void dfs(int node) {
	used[node] = 1;
	for(vector <int> :: iterator it = dag[node].begin() ; it != dag[node].end() ; ++ it)
		if(!used[*it])
			dfs(*it);
	tsort.push_back(node);
}

int main() {
	get(t);
	while(t -- ) {
		get(n);
		get(m);
		for(int i = 1 ; i <= m ; ++ i) {
			int x, y, z;
			get(x);
			get(y);
			get(z);
			g[x].push_back(edge(y, z, i));
		}
		dijkstra();
		for(int i = 2 ; i <= n ; ++ i)
			for(vector <edge> :: iterator it = g[i].begin() ; it != g[i].end() ; ++ it)
				if(dp[it->x] == dp[i] + it->y)
					dag[dad[i]].push_back(it->ind);
		tsort.clear();
		for(int i = 1 ; i <= m ; ++ i)
			if(!used[i])
				dfs(i);
		reverse(tsort.begin(), tsort.end());
		for(int i = 0 ; i < tsort.size() ; ++ i)
			fout << tsort[i] << ' ';
		fout << '\n';
		for(int i = 1 ; i <= n ; ++ i)
			g[i].clear();
		for(int i = 0 ; i <= m ; ++ i)
			dag[i].clear();	
		used.reset();
	}
}
