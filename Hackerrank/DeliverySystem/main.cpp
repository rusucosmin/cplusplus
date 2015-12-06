#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <string.h>

using namespace std;

const int maxn = 100005;

vector <int> g[maxn], gt[maxn], dag[maxn], c[maxn];
int t, n, m, k, where[maxn], sz;
vector <int> v, discovered, act, tsort;
vector <vector <int> > ctc;
bitset <maxn> used, special;

void dfs(int node) {
	used[node] = 1;
	for(auto it : g[node])
		if(!used[it])
			dfs(it);
	discovered.push_back(node);
}

void dfs2(int node) {
	used[node] = 0;
	where[node] = ctc.size() + 1;
	act.push_back(node);
	for(auto it : gt[node])
		if(used[it])
			dfs2(it);	
}

void dfs3(int node) {
	used[node] = 1;
	for(auto it : dag[node])
		if(!used[it])
			dfs3(it);
	tsort.push_back(node);
}

int dp[maxn];

inline void builddp() {
	for(int i = sz - 1 ; i >= 0 ; -- i) {
		dp[tsort[i]] = special[tsort[i]];
		for(auto it : dag[tsort[i]])
			dp[tsort[i]] = max(dp[tsort[i]], dp[it] + special[tsort[i]]);
	}
}

int main() {
	#ifdef HOME
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
	#endif
	cin >> t;
	while(t -- ) {
		cin >> n >> m >> k;
		for(int i = 0 ; i < k ; ++ i) {
			int x;
			cin >> x;
			v.push_back(x);
		}
		for(int i = 0 ; i < m ; ++ i) {
			int x, y;
			cin >> x >> y;
			g[x].push_back(y);
			gt[y].push_back(x);
		}
		for(int i = 1 ; i <= n ; ++ i)
			if(!used[i])
				dfs(i);
		for(auto it = discovered.rbegin() ; it != discovered.rend() ; ++ it)
			if(used[*it]) {
				act.clear();
				dfs2(*it); 
				ctc.push_back(act);
			}

		sz = ctc.size();

		for(int i = 1 ; i <= n ; ++ i) {
			for(auto it : g[i])
				if(where[i] != where[it])
					dag[where[i]].push_back(where[it]);
		}
		for(int i = 1 ; i <= sz ; ++ i)
			if(!used[i])
				dfs3(i);
		reverse(tsort.begin(), tsort.end());

		for(int i = 0 ; i < k ; ++ i) {
			special[where[v[i]]] = 1;
			c[where[v[i]]].push_back(v[i]);
		}

		used.reset();
		builddp();

		int stnode = 0;
		for(int i = 0 ; i < tsort.size() ; ++ i)
			if(special[tsort[i]]) {
				stnode = tsort[i];
				break;
			}
		vector <int> ans;
		while(stnode) {
			sort(c[stnode].begin(), c[stnode].end());
			for(auto it : c[stnode])
				ans.push_back(it);
			int nxt = 0;
			for(auto it : dag[stnode]) {
				if(dp[it] + special[stnode] == dp[stnode]) {
					nxt = it;
					break;
				}
			}
			stnode = nxt;
		}

		if(ans.size() == k) 
			for(auto comp : ans)
				cout << comp << ' ';
		else
			cout << "-1";
		cout << '\n';

		memset(dp, 0, sizeof(dp));
		special.reset();
		used.reset();
		tsort.clear();
		v.clear();
		for(int i = 1 ; i <= n ; ++ i) {
			g[i].clear();
			c[i].clear();
			gt[i].clear();
			dag[i].clear();
		}
		discovered.clear();
		ctc.clear();
	}
}
