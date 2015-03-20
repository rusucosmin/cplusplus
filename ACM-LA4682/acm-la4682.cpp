#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <assert.h>

using namespace std;

const int maxn = 100005;

struct trie {
	trie *sons[2];
	trie () {
		memset(sons, 0, sizeof(sons));
	}
} *root = new trie();

inline void insert(trie *node, int x, int bit) {
	if(bit == -1)
		return ;
	bool son = (x & (1 << bit));
	if(!node->sons[son])
		node->sons[son] = new trie();
	insert(node->sons[son], x, bit - 1);
}

inline int query(trie *node, int x, int bit) {
	if(bit == -1)
		return 0;
	bool son = (x & (1 << bit));
	if(node->sons[!son])
		return (1 << bit) + query(node->sons[!son], x, bit - 1);
	else if(node->sons[son])
		return query(node->sons[son], x, bit - 1);
	else
		assert(false);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("acm-la4682.in", "r", stdin);
	freopen("acm-la4682.out", "w", stdout);
	#endif
	int t, n;
	cin >> t;
	while(t -- ){
		root = new trie();
		cin >> n;
		int sum_xor = 0;
		int ans = 0;
		insert(root, sum_xor, 31);
		for(int i = 1 ; i <= n ; ++ i) {
			int x;
			cin >> x;
			sum_xor = sum_xor ^ x;
			insert(root, sum_xor, 31);
			ans = max(ans, query(root, sum_xor, 31));
			ans = max(ans, sum_xor);
		}
		cout << ans << '\n';
	}

}
