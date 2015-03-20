#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include <bitset>

using namespace std;

const int maxn = 505;

int n, m, q, p[maxn], age[maxn];
vector <int> g[maxn], path[maxn];
bitset <maxn> used;

inline void dfs(int node, int father) {
	used[node] = 1;
	path[father].push_back(node);
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
		if(!used[*it])
			dfs(*it, father);
}

int main() {
	#ifndef ONILNE_JUDGE
	freopen("uri1469.in", "r", stdin);
	freopen("uri1469.out", "w", stdout);
	#endif
	while(cin >> n >> m >> q) {
		for(int i = 1 ; i <= n ; ++ i) {
			cin >> age[i];
			p[i] = i;
		}	
		for(int i = 1 ; i <= m ; ++ i) {
			int x, y;
			cin >> x >> y;
			g[y].push_back(x);
		}
		for(int i = 1 ; i <= n ; ++ i) {
			used.reset();
			used[i] = 1;
			for(vector <int> :: iterator it = g[i].begin() ; it != g[i].end() ; ++ it)	
				if(!used[*it])
					dfs(*it, i);
		}
		while (q--) {
			char c;
			cin >> c;
			if(c == 'T') {
				int x, y;
				cin >> x >> y;
				swap(age[p[x]], age[p[y]]);
				swap(p[x], p[y]);
			}
			else {
				int x, ans = 0x3f3f3f3f;
				cin >> x;
				for(vector <int> :: iterator it = path[p[x]].begin() ; it != path[p[x]].end() ; ++ it)
					ans = min(ans, age[*it]);
				if(ans == 0x3f3f3f3f)
					cout << "*\n";
				else
					cout << ans << '\n';
			}
		}
	}

}
