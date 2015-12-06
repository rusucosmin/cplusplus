#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <bitset>
#include <string.h>

using namespace std;

ifstream fin("apm.in");
ofstream fout("apm.out");

const int maxn = 200005;

int n, m, father[maxn];

inline int find(int x) {
	if(father[x] != x)
		father[x] = find(father[x]);
	return father[x];
}

inline bool unite(int x, int y) {
	x = find(x);
	y = find(y);
	if(x == y)
		return false;
	father[x] = y;
	return true;
}

inline void kruskal() {
	vector <pair<int, pair<int, int> > > edges;
	fin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i)
		father[i] = i;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y, z;
		fin >> x >> y >> z;
		edges.push_back(make_pair(z, make_pair(x, y)));
	}
	sort(edges.begin(), edges.end());
	int total = 0;
	vector <pair<int, int> > apm;
	for(int i = 0 ; i < edges.size() ; ++ i) {
		if(unite(edges[i].second.first, edges[i].second.second)) {
			total += edges[i].first;
			apm.push_back(edges[i].second);
		}
	}
	fout << total << '\n' << n - 1 << '\n';
	for(auto it : apm)
		fout << it.first << ' ' << it.second << '\n';
}

const int oo = 0x3f3f3f3f;
vector <pair<int, int> > g[maxn];
int dist[maxn];
bitset <maxn> used;

inline void prim() {
	fin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y, z;
		fin >> x >> y >> z;
		g[x].push_back(make_pair(y, z));
		g[y].push_back(make_pair(x, z));
	}
	priority_queue <pair<int, int> > q;
	memset(dist, oo, sizeof(dist));
	dist[1] = 0;
	q.push(make_pair(0, 1));
	used[1] = 1;
	vector <pair<int, int> > apm;
	int ans = 0;
	while(!q.empty()) {
		int cost = -q.top().first;
		int node = q.top().second;	
		q.pop();
		if(dist[node] != cost)
			continue;
		if(!used[node]) {
			used[node] = 1;
			apm.push_back(make_pair(father[node], node));
			ans += cost;
		}
		for(auto it : g[node])
			if(dist[it.first] > it.second && !used[it.first]) {
				dist[it.first] = it.second;
				father[it.first] = node;
				q.push(make_pair(-dist[it.first], it.first));	
			}
	}
	fout << ans << '\n' << n - 1 << '\n';
	for(auto it : apm)
		fout << it.first << ' ' << it.second << '\n';
}

int main() {
//	kruskal();
	prim();
}
