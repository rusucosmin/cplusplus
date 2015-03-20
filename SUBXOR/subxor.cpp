#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

const int sigma = 2;

struct trie {
	trie *sons[sigma];
	int cnt[sigma];
	trie() {
		memset(sons, 0, sizeof(sons));
		memset(cnt, 0, sizeof(cnt));
	}
	int getcnt(int son) {
		return cnt[son];
	}
} *root;

inline void insert(trie *node, int x, int level) {
	if(level == -1)
		return ;
	bool son = (x & (1 << level));
	++ node->cnt[son];
	if(!node->sons[son])
		node->sons[son] = new trie();
	insert(node->sons[son], x, level - 1);
}

inline int query(trie *node, int x, int k, int level) {
	if(level == -1 || !node)
		return 0;
	bool bitk = (k & (1 << level));
	bool bitx = (x & (1 << level));
	if(bitk == 0)
		return query(node->sons[bitx], x, k, level - 1);
	else /// bitk == 1
		return node->getcnt(bitx) + query(node->sons[!bitx], x, k, level - 1);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("subxor.in", "r", stdin);
	freopen("subxor.out", "w", stdout);
	#endif
	int n, k, t;
	cin >> t;
	while(t -- ) {
		root = new trie();
		cin >> n >> k;
		int sum = 0;
		long long ans = 0;
		insert(root, 0, 30);
		for(int i = 1 ; i <= n ; ++ i) {
			int x;
			cin >> x;
			sum = sum ^ x;	
			ans += query(root, sum, k, 30);
			insert(root, sum, 30);
		}
		cout << ans << '\n';
	}
}
