#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

const int sigma = 2;
const int maxn = 205;

char s[maxn];
int n, t;

struct trie {
	trie *sons[sigma];
	int fr;
	trie () {
		memset(sons, 0, sizeof(sons));
		fr = 0;
	}
} *root;

inline void insert(trie *node, char *s) {
	if(!*s) {
		++ node->fr;
		return ;
	}
	++ node->fr;
	int son = *s - '0';
	if(!node->sons[son])
		node->sons[son] = new trie();
	insert(node->sons[son], s + 1);
}

inline int dfs(trie *node, int level) {
	if(!node)
		return 0;
	int ans = level * node->fr;
	for(int i = 0 ; i < sigma ; ++ i)
		if(node->sons[i])
			ans = max(ans, dfs(node->sons[i], level + 1));
	return ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("11488.in", "r", stdin);
	freopen("11488.out", "w", stdout);
	#endif

	cin >> t;
	while(t -- ) {
		root = new trie();
		cin >> n;
		cin.get();
		for(int i = 0 ; i < n ; ++ i) {
			cin.getline(s, maxn);
			insert(root, s);
		}
		cout << dfs(root, 0) << '\n';
	}

}
