#include <vector>
#include <set>
#include <stack>
#include <string.h>
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <bitset>

using namespace std;

const int maxn = 200005;
const int oo = 0x3f3f3f3f;

int n, m, nodes, indecs, idx[maxn], lowlink[maxn], comp;
unordered_map<string, int> id;
vector <int> g[maxn], dag[maxn];
pair <int, int> info[maxn], dp[maxn];
vector <string> text;
stack <int> st;
bitset <maxn> inst, used;
int where[maxn];
pair<int, int> ans;

inline void tolower(string &s) {
	for(int i = 0 ; i < s.size() ; ++ i)
		s[i] = tolower(s[i]);
}

inline int get(string &s, char a) {
	int ret = 0;
	for(int i = 0 ; i < s.size() ; ++ i)
		ret += s[i] == a;
	return ret;
}

inline void tarjan(int node) {
	idx[node] = lowlink[node] = ++ indecs;	
	st.push(node);
	inst[node] = 1;
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
		if(!idx[*it]) {
			tarjan(*it);
			lowlink[node] = min(lowlink[node], lowlink[*it]);
		}
		else if(inst[*it])
			lowlink[node] = min(lowlink[node], lowlink[*it]);

	if(idx[node] == lowlink[node]) {
		++ comp;
		dp[comp] = info[node];
		int nod;
		do {
			inst[nod = st.top()] = false;
			st.pop();
			where[nod] = comp;
			if(dp[comp].first > info[nod].first || (dp[comp].first == info[nod].first && dp[comp].second > info[nod].second))
				dp[comp] = info[nod];
		} while(nod != node);
	}
}

inline void getSCC() {
	for(int i = 1 ; i <= nodes ; ++ i)
		if(!idx[i])
			tarjan(i);
	
	for(int i = 1 ; i <= nodes ; ++ i)
		for(vector <int> :: iterator it = g[i].begin() ; it != g[i].end() ; ++ it)
			if(where[i] != where[*it])
				dag[where[i]].push_back(where[*it]);
}

inline void dfs(int node) {
	used[node] = 1;
	for(vector <int> :: iterator it = dag[node].begin() ; it != dag[node].end() ; ++ it) {
		if(!used[*it])
			dfs(*it);
		if(dp[node].first > dp[*it].first || (dp[node].first == dp[*it].first && dp[node].second > dp[*it].second))
			dp[node] = dp[*it];
	}
}

inline void solve() {
	for(int i = 1 ; i <= comp ; ++ i)
		if(!used[i])
			dfs(i);
	pair<long long, long long> ans = make_pair(0, 0);
	for(vector <string> :: iterator it = text.begin() ; it != text.end() ; ++ it) {
		int node = where[id[*it]];
		ans.first += dp[node].first;
		ans.second += dp[node].second;
	}
	cout << ans.first << ' ' << ans.second << '\n';
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("476d.in", "r", stdin);
	freopen("476d.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		string s;
		cin >> s;
		tolower(s);
		text.push_back(s);
		if (!id[s]) {
			id[s] = ++ nodes;
			info[id[s]] = make_pair(get(s, 'r'), s.size());
		}	
	}
	cin >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		string a, b;
		cin >> a;
		cin >> b;
		tolower(a);
		tolower(b);
		if(!id[a]) {
			id[a] = ++ nodes;
			info[id[a]] = make_pair(get(a, 'r'), a.size());
		}
		if(!id[b]) {
			id[b] = ++ nodes;
			info[id[b]] = make_pair(get(b, 'r'), b.size());
		}
		g[id[a]].push_back(id[b]);
	}
	getSCC();	
	solve();
		
}
