#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <stack>

using namespace std;

const int maxn = 100005;

vector <int> g[maxn], gt[maxn], discovered;
int n, m;
vector <vector <int> > ctc;
bitset <maxn> used;

inline void dfs(int node) {
	used[node] = 1;
	for(auto it : g[node])
		if(!used[it])
			dfs(it);
	discovered.push_back(node);
}

inline void dfs(int node, vector <int> &act) {
	act.push_back(node);
	used[node] = 0;
	for(auto it : gt[node])
		if(used[it])
			dfs(it, act);
}

inline void kosaraju() {
	ifstream fin("ctc.in");
	ofstream fout("ctc.out");
	fin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		fin >> x >> y;
		g[x].push_back(y);
		gt[y].push_back(x);
	}
	for(int i = 1 ; i <= n ; ++ i)
		if(!used[i])
			dfs(i);
	reverse(discovered.begin(), discovered.end());
	for(auto it : discovered)
		if(used[it]) {
			vector <int> act;
			dfs(it, act);
			ctc.push_back(act);
		}
	fout << ctc.size() << '\n';
	for(auto comp : ctc) {
		for(auto it : comp)
			fout << it << ' ';
		fout << '\n';
	}
}

int depth[maxn], ind, lowlink[maxn];
bitset <maxn> inst;
stack <int> st;

inline void tarjan(int node) {
	depth[node] = lowlink[node] = ++ ind;	
	st.push(node);
	inst[node] = 1;
	for(auto it : g[node]) {
		if(!depth[it]) {
			tarjan(it);
			lowlink[node] = min(lowlink[node], lowlink[it]);
		}
		else if(inst[it])
			lowlink[node] = min(lowlink[node], lowlink[it]);
	}
	cerr << node << ' ' << depth[node] << ' ' << lowlink[node] << '\n';
	if(depth[node] == lowlink[node]) {
		vector <int> act;
		int other;
		do {
			other = st.top();
			st.pop();
			inst[other] = false;
			act.push_back(other);
		}while(other != node);
		ctc.push_back(act);
	}
}

inline void tarjanalg() {
	ifstream fin("ctc.in");
	ofstream fout("ctc.out");
	fin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		fin >> x >> y;
		g[x].push_back(y);
	}
	for(int i = 1 ; i <= n ; ++ i)
		if(!depth[i])
			tarjan(i);
	fout << ctc.size() << '\n';
	for(auto comp : ctc) {
		for(auto it : comp)
			fout << it << ' ';
		fout << '\n';
	}
}

int main() {
//	kosaraju();
	tarjanalg();
}
