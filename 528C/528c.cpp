#include <iostream>
#include <fstream>
#include <string.h>
#include <stack>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 100005;

int n, m, deg[maxn];
vector <int> g[maxn];
vector <int> cycle;

inline void euler(int stnode) {
	stack <int> st;
	st.push(stnode);
	while(!st.empty()) {
		int node = st.top();
		if(g[node].size()) {
			int newnode = g[node].back();
			g[node].pop_back();
			g[newnode].erase(find(g[newnode].begin(), g[newnode].end(), node));
			st.push(newnode);
		}
		else {
			cycle.push_back(node);
			st.pop();
		}
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("528c.in", "r", stdin);
	freopen("528c.out", "w", stdout);
	#endif
	cin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
		++ deg[x];
		++ deg[y];
	}
	int last = -1;
	for(int i = 1 ; i <= n ; ++ i)
		if(deg[i] % 2 == 1)
			if(last == -1)
				last = i;
			else {
				++ m;
				g[i].push_back(last);
				g[last].push_back(i);
				last = -1;
			}
	if(m & 1) {
		++ m;
		g[1].push_back(1);
		g[1].push_back(1);
	}
	euler(1);
	cout << m << '\n';
	int cnt = 0;
	for(int i = 0 ; i + 1 < cycle.size() ; ++ i) {
		if(i % 2 == 0)
			cout << cycle[i] << ' ' << cycle[i + 1] << '\n';
		else
			cout << cycle[i + 1] << ' ' << cycle[i] << '\n';
	}
}
