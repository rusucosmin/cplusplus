#include <fstream>
#include <stack>
#include <vector>
#include <iostream>
#include <bitset>

using namespace std;

const int maxn = 100005;
const int mod = 1000000007;

int n, m, ans2 = 1, a[maxn], lowlink[maxn], idx[maxn], indecs, sccmin[maxn], sccnb[maxn], scc;
long long ans1;
vector <int> g[maxn];
stack <int> st;
bitset <maxn> inst;

inline void dfs(int node) {
	idx[node] = lowlink[node] = ++indecs;
	inst[node] = 1;
	st.push(node);
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
		if(!idx[*it]) {
			dfs(*it);
			lowlink[node] = min(lowlink[node], lowlink[*it]);
		}
		else
			if(inst[*it])
				lowlink[node] = min(lowlink[node], lowlink[*it]);
	if(lowlink[node] == idx[node]) {
		int nod;
		sccmin[++ scc] = 0x3f3f3f3f;
		do {
			inst[nod = st.top()] = 0;
			st.pop();
			if(sccmin[scc] > a[nod]) {
				sccmin[scc] = a[nod];
				sccnb[scc] = 1;
			}
			else if(sccmin[scc] == a[nod])
				++ sccnb[scc];
		} while(node != nod);
		ans1 += sccmin[scc];
		ans2 = (1LL * ans2 * sccnb[scc]) % mod;
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("427c.in", "r", stdin);
	freopen("427c.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i)	cin >> a[i];
	cin >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
	}

	for(int i = 1 ; i <= n ; ++ i)
		if(!idx[i])
			dfs(i);

	cout << ans1 << ' ' << ans2 << '\n';
}
