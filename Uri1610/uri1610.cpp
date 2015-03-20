#include <iostream>
#include <string.h>
#include <bitset>
#include <vector>
#include <stack>

using namespace std;

const int maxn = 10005;

int t, n, m, indecs, idx[maxn], lowlink[maxn];
vector <int> g[maxn];
stack <int> st;
bitset <maxn> inst;
bool okay;

inline void tarjan(int node) {	
	idx[node] = lowlink[node] = ++ indecs;
	st.push(node);
	inst[node] = 1;
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
		if(!idx[*it]) {
			tarjan(*it);
			lowlink[node] = min(lowlink[node], lowlink[*it]);
		}
		else
			if(inst[*it])
				lowlink[node] = min(lowlink[node], lowlink[*it]);
	if(idx[node] == lowlink[node]) {
		int act = 0;
		int nod;
		do {
			nod = st.top();
			st.pop();
			inst[nod] = false;
			++ act;
		} while( nod != node );
		if(act != 1)
			okay = false;	
	}
}

int main() {
	#ifndef ONLINE_JUDGE
		freopen("uri1610.in", "r", stdin);
		freopen("uri1610.out", "w", stdout);
	#endif
	cin >> t;
	while (t --) {
		okay = true;
		cin >> n >> m;
		indecs = 0;
		memset(idx, 0, sizeof(idx));
		memset(lowlink, 0, sizeof(lowlink));
		while(!st.empty()) {
			inst[st.top()] = false;
			st.pop();
		}
		for(int i = 1 ; i <= m ; ++ i) {
			int x, y;
			cin >> x >> y;
			g[x].push_back(y);
		}
		for(int i = 1 ; i <= n ; ++ i)
			if(!idx[i])
				tarjan(i);
			
		if(!okay)
			cout << "SIM\n";
		else
			cout << "NAO\n";
		for(int i = 1 ; i <= n ; ++ i)
			vector <int> ().swap(g[i]);
	}
	
}
