#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <stack>

using namespace std;

const int maxn = 100005;

int n, m, dflevel[maxn], lowlink[maxn];
vector <int> g[maxn];
vector <set<int> > bcc;
stack <pair<int, int> > st;

inline void extractbcc(int x, int y) {
	int tx, ty;
	set <int> act;
	do {
		tx = st.top().first;
		ty = st.top().second;
		st.pop();
		act.insert(tx);
		act.insert(ty);
	}while(tx != x || ty != y);
	bcc.push_back(act);
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

int main() {
	ifstream fin("biconex.in");
	ofstream fout("biconex.out");
	fin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		fin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(1, 0);
	fout << bcc.size() << '\n';
	for(auto comp : bcc) {
		for(auto it : comp)
			fout << it << ' ';
		fout << '\n';
	}
}
