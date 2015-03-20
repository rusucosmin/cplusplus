#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
#include <set>
#include <bitset>

using namespace std;

const int maxn = 100005;

vector <int> g[maxn];
int n, m, level[maxn], df[maxn];
stack <pair<int, int> > st;
vector <set<int> > bcc;
bitset <maxn> used;

inline void extractbcc(int x, int y) {
	set<int> act;	
	int tx, ty;
	do {
		tx = st.top().first;
		ty = st.top().second;
		act.insert(tx);
		act.insert(ty);
		st.pop();
	}while(x != tx || y != ty);
	bcc.push_back(act);
}

inline void dfs(int node, int father) {
	level[node] = level[father] + 1;
	df[node] = level[node];
	used[node] = 1;
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
		if(*it == father)
			continue;
		if(!used[*it]) {
			st.push(make_pair(node, *it));
			dfs(*it, node);
			df[node] = min(df[node], df[*it]);
			if(df[*it] >= level[node]) {
				extractbcc(node, *it);
			}
		}
		else
			df[node] = min(df[node], level[*it]);

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
	for(int i = 1 ; i <= n ; ++ i)
		if(!used[i])
			dfs(i, 0);
	
	fout << bcc.size() << '\n';
	for(vector <set<int> > :: iterator comp = bcc.begin() ; comp != bcc.end() ; ++ comp, fout << '\n')
		for(set<int> :: iterator it = comp->begin() ; it != comp->end() ; ++ it)
			fout << *it << ' ';
}
