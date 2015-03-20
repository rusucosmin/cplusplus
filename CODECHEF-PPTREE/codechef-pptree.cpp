#include <iostream>
#include <vector>
#include <string.h>
#include <cassert>

using namespace std;

const int maxn = 100005;

int t, n, m, s[maxn];
vector <pair<int, int> > g[maxn];
	
inline void dfs(int node, int father) {
	for(auto it : g[node])
		if(it.first != father) {
			s[it.first] = s[node] ^ it.second;
			dfs(it.first, node);
		}
}

struct trie {
	trie *sons[2];
	trie() {
		memset(sons, 0, sizeof(sons));
	}
} *root;

inline void insert(trie *node, int x, int bit) {
	if(bit == -1)
		return ;
	bool son = x & (1 << bit);
	if(!node->sons[son])
		node->sons[son] = new trie();
	insert(node->sons[son], x, bit - 1);
}

inline int query(trie *node, int x, int bit) {
	if(bit == -1)
		return 0;
	bool son = x & (1 << bit);
	if(node->sons[!son])
		return (1 << bit) + query(node->sons[!son], x, bit - 1);
	else
		if(node->sons[son])
			return query(node->sons[son], x, bit - 1);
		else
			assert(false);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("codechef-pptree.in", "r", stdin);
	freopen("codechef-pptree.out", "w", stdout);
	#endif
	cin >> t;
	while(t -- ) {
		root = new trie();
		cin >> n;
		for(int i = 1 ; i < n ; ++ i) {
			int x, y, z;
			cin >> x >> y >> z;
			g[x].push_back(make_pair(y, z));
			g[y].push_back(make_pair(x, z));
		}
		dfs(1, 0);
		int ans = 0;
		for(int i = 1 ; i <= n ; ++ i) {
			insert(root, s[i], 31);
			ans = max(ans, query(root, s[i], 31));
		}
		cout << ans << '\n';
		for(int i = 1 ; i <= n ; ++ i) {
			s[i] = 0;
			vector <pair<int, int> > ().swap(g[i]);
		}
	}
}
