#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <bitset>

using namespace std;

const int maxn = 100005;

vector <pair<int, int> > g[maxn];
int x[maxn], y[maxn], n, m, t, level[maxn];
bitset <maxn> ans, used;

inline void addedge(int ind, int x, int y) {
	if(x < y)
		ans[ind] = 0;
	else
		ans[ind] = 1;
}

inline void dfs(int node, int father) {
	used[node] = 1;
	level[node] = level[father] + 1;
	for(auto it : g[node]) {
		if(it.first == father)
			continue;
		if(!used[it.first]) {
			dfs(it.first, node);
			addedge(it.second, node, it.first);
		}
		else
			if(level[it.first] < level[node])
				addedge(it.second, node, it.first);
	}
}

const int lim = (1 << 20);
int pos;
char buff[lim];

inline void getint(int &x) {
	x = 0;
	while(!isdigit(buff[pos]))
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	while(isdigit(buff[pos])) {
		x = x * 10 + buff[pos] - '0';
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}
}

int main() {
	freopen("comoditate.in", "r", stdin);
	freopen("comoditate.out", "w", stdout);
	getint(t);
	while(t --) {
		getint(n);
		getint(m);
		for(int i = 1 ; i <= m ; ++ i) {
			int x, y;
			getint(x);
			getint(y);
			g[x].push_back(make_pair(y, i));
			g[y].push_back(make_pair(x, i));
		}
		dfs(1, 0);
		for(int i = 1 ; i <= m ; ++ i)
			cout << ans[i];
		cout << '\n';
		ans.reset();
		used.reset();
		memset(level, 0, sizeof(level));
		for(int i = 1 ; i <= n ; ++ i)
			vector <pair<int, int> > ().swap(g[i]);
	}
}
