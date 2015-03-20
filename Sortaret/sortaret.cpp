#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

const int maxn = 100005;

vector <int> st, g[maxn];
int n, m;
bitset <maxn> used;

inline void dfs(int node) {
	used[node] = 1;
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
		if(!used[*it])
			dfs(*it);
	st.push_back(node);
}


int main() {
	ifstream fin("sortaret.in");
	ofstream fout("sortaret.out");
	fin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		fin >> x >> y;
		g[x].push_back(y);
	}
	for(int i = 1 ; i <= n ; ++ i)
		if(!used[i])
			dfs(i);
	reverse(st.begin(), st.end());
	for(vector <int> :: iterator it = st.begin() ; it != st.end() ; ++ it)
		fout << *it << ' ';
}
