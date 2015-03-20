#include <fstream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <iostream>
#include <string.h>

using namespace std;

const int maxn = 100005;

unordered_map <int, stack<int> > st;
int n, m, a[maxn], ans[maxn], level[maxn];
vector <int> g[maxn];

inline void dfs(int node, int father) {
	level[node] = level[father] + 1;
	int aux = a[node];
	vector <int> ds;
	for(int d = 2 ; d * d <= aux ; ++ d) {
		if(aux % d)
			continue;
		if(!st[d].empty())
			if(level[ans[node]] < level[st[d].top()])
				ans[node] = st[d].top();

		st[d].push(node);
		ds.push_back(d);

		while(aux % d == 0)
			aux /= d;
	}
	if(aux > 1) {
		if(!st[aux].empty())
			if(level[ans[node]] < level[st[aux].top()])
				ans[node] = st[aux].top();
		ds.push_back(aux);	
		st[aux].push(node);
	}
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
		if(*it == father)
			continue;
		dfs(*it, node);
	}
	for(auto it : ds)
		st[it].pop();
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("463e.in", "r", stdin);
	freopen("463e.out", "w", stdout);
	#endif

	cin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> a[i];
	for(int i = 1 ; i < n ; ++ i) {
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(1, 1);
	for(int i = 1 ; i <= m ; ++ i) {
		int op, x, y;
		cin >> op >> x;
		if(op == 1) {
			if(ans[x] > 0)	
				cout << ans[x] << '\n';
			else
				cout << "-1\n";
		}
		else {
			memset(ans, 0, sizeof(ans));
			cin >> a[x];
			st.clear();
			dfs(1, 0);
		}
	}
}
