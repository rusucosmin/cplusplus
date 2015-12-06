#include <fstream>
#include <vector>
#include <queue>
#include <bitset>
#include <string.h>
#include <iostream>
#include <set>
#include <cassert>

using namespace std;

const int maxn = 5005;

vector <int> g[maxn];
int deg[maxn], n, dist[maxn];
bitset <maxn> used;

inline vector <int> getdiameter() {
	queue <int> q;
	memset(dist, 0, sizeof(dist));
	for(int i = 1 ; i <= n ; ++ i)
		if(deg[i] == 1) {
			q.push(i);
			dist[i] = 0;
		}
	int diameter = 0;
	while(!q.empty()) {
		int node = q.front();
		q.pop();
		for(auto it : g[node]) {
			if(-- deg[it] == 1) {
				q.push(it);
				dist[it] = dist[node] + 1;
				diameter = max(diameter, dist[it]);
			}
		}
	}
	vector <int> ret;
	for(int i = 1 ; i <= n ; ++ i) 
		if(dist[i] == diameter)
			ret.push_back(i);
	return ret;
}

inline void dfs(int node, int father, int &maxd) {
	dist[node] = dist[father] + 1;
	maxd = max(maxd, dist[node]);
	for(auto it : g[node])
		if(it != father)
			dfs(it, node, maxd);
}

inline vector <int> getworstroots(int bestroot) {
	int maxd = 0;
	used.reset();
	dfs(bestroot, 0, maxd);
	int merge = 0;
	for(int i = 1 ; i <= n ; ++ i)
		if(dist[i] == maxd) {
			used[i] = 1;
			if(merge)
				continue;
			merge = i;
		}
	dfs(merge, 0, maxd);
	for(int i = 1 ; i <= n ; ++ i)
		if(dist[i] == maxd)
			used[i] = 1;
	vector <int> ret;
	for(int i = 1 ; i <= n ; ++ i)
		if(used[i])
			ret.push_back(i);
	return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uva-10459.in", "r", stdin);
	freopen("uva-10459.out", "w", stdout);
	#endif
	bool test = false;
	while(cin >> n) {
		test = 1;
		for(int i = 1 ; i <= n ; ++ i) {
			cin >> deg[i];
			for(int j = 0 ; j < deg[i] ; ++ j) {
				int x;
				cin >> x;
				g[i].push_back(x);
			}
		}
		vector <int> bestroots = getdiameter();
		cout <<  "Best Roots  :";
		assert(bestroots.size() <= 2);
		for(int i = 0 ; i < bestroots.size() ; ++ i)
			cout << ' ' << bestroots[i];
		cout << '\n';
		vector <int> worstroots = getworstroots(bestroots[0]);
		cout << "Worst Roots :";
		for(int i = 0 ; i < worstroots.size() ; ++ i)
			cout << ' ' << worstroots[i];
		cout << '\n';
		for(int i = 1 ; i <= n ; ++ i)
			vector <int> ().swap(g[i]);
	}
}
