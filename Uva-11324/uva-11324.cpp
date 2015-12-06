#include <iostream>
#include <fstream>
#include <queue>
#include <bitset>
#include <algorithm>
#include <stack>
#include <string.h>

using namespace std;

const int maxn = 1005;

vector <int> g[maxn], dag[maxn], tsort;
int t, n, m, comps, ind[maxn], lowlink[maxn], indecs, where[maxn], dist[maxn], sz[maxn];
bitset <maxn> inst, used;
stack <int> st;

inline void tarjan(int node) {
	ind[node] = lowlink[node] = ++ indecs;
	st.push(node);
	inst[node] = 1;
	for(auto it : g[node])
		if(!ind[it]) {
			tarjan(it);
			lowlink[node] = min(lowlink[node], lowlink[it]);
		}
		else if(inst[it])
			lowlink[node] = min(lowlink[node], lowlink[it]);
	if(lowlink[node] == ind[node]) {
		++ comps;	
		int x;
		do {
			x = st.top();
			st.pop();
			inst[x] = 0;
			where[x] = comps;
			++ sz[comps];
		} while(x != node);
	}
}

inline void dfs(int node) {
	used[node] = 1;
	for(auto it : dag[node])
		if(!used[it])
			dfs(it);
	tsort.push_back(node);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uva-11324.in", "r", stdin);
	freopen("uva-11324.out", "w", stdout);
	#endif
	cin >> t;
	while(t --){
		cin >> n >> m;
		for(int i = 1 ; i <= m ; ++ i) {
			int x, y;
			cin >> x >> y;
			g[x].push_back(y);
		}
		for(int i = 1 ; i <= n ; ++ i)
			if(!ind[i])
				tarjan(i);
		for(int i = 1 ; i <= n ; ++ i)
			for(auto it : g[i])
				if(where[i] != where[it])
					dag[where[i]].push_back(where[it]);
		for(int i = 1 ; i <= comps ; ++ i)
			if(!used[i])
				dfs(i);
		reverse(tsort.begin(), tsort.end());
		int ans = 0;
		for(int i = 0 ; i < tsort.size() ; ++ i) {
			int node = tsort[i];
			if(dist[node] == 0)
				dist[node] = sz[node];
			ans = max(ans, dist[node]);
			for(auto it : dag[node])
				dist[it] = max(dist[it], dist[node] + sz[it]);
		}
		cout << ans << '\n';
		while(!st.empty())
			st.pop();
		inst.reset();
		used.reset();
		for(int i = 1 ; i <= n ; ++ i)
			vector <int> ().swap(g[i]);
		for(int i = 1 ; i <= comps ; ++ i)
			vector <int> ().swap(dag[i]);
		memset(ind, 0, sizeof(ind));
		memset(lowlink, 0, sizeof(lowlink));
		indecs = 0;
		comps = 0;
		vector <int> ().swap(tsort);
		memset(dist, 0, sizeof(dist));
		memset(sz, 0, sizeof(sz));
	}
	
}
