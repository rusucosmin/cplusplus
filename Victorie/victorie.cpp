#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <vector>
#include <set>
#include <stack>

using namespace std;

ifstream fin("victorie.in");
ofstream fout("victorie.out");

const int maxn = 100005;

vector <int> g[maxn];
stack <pair<int, int> > st;
int n, m, dflevel[maxn], cnt, lowlink[maxn], ans, where[maxn];
bitset <maxn> used, ok;
vector <set<int> > bcc;

inline void extractbcc(int x, int y) {
	int tx, ty;
	set <int> s;
	++ cnt;
	do {
		tx = st.top().first;
		ty = st.top().second;
		st.pop();
		s.insert(tx);
		s.insert(ty);
	} while(x != tx || y != ty);
	bcc.push_back(s);
}

inline void dfs(int node, int father) {
	dflevel[node] = lowlink[node] = dflevel[father] + 1;
	for(auto it : g[node]) {
		if(it == father)	
			continue;
		if(!dflevel[it]) {
			st.push(make_pair(node, it));
			dfs(it, node);
			lowlink[node] = min(lowlink[node], lowlink[it]);
			if(lowlink[it] >= dflevel[node])
				extractbcc(node, it);
		}
		else
			lowlink[node] = min(lowlink[node], dflevel[it]);
	}
}

inline void df(int node, int comp) {
	used[node] = 1;
	for(auto it : g[node])
		if(where[it] == comp) {
			if(!used[it])
				df(it, comp);
			else
				if(it != node && dflevel[node] % 2 == dflevel[it] % 2)
					ok[comp] = 1;
		}
}

int main() {
	fin >> n >> m;
	while(m --) {
		int x, y;
		fin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	for(int i = 1 ; i <= n ; ++ i)
		if(!dflevel[i]) {
			dfs(i, 0);
			while(!st.empty())
				st.pop();
		}
	set<int> ans;
	for(int i = 1 ; i <= cnt ; ++ i) {
		int node = *bcc[i - 1].begin();
		for(auto it : bcc[i - 1])
			where[it] = i;
		used.reset();
		df(node, i);
		if(ok[i])
			for(auto it : bcc[i - 1])
				ans.insert(it);
	}
	fout << ans.size() << '\n';
	for(auto it : ans)
		fout << it << ' ';
}
