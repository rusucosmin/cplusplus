#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

const int sigma = 26;
const int maxn = 100005;

struct trie {
	trie *sons[sigma];
	bool win, lose;
	trie() {
		memset(sons, 0, sizeof(sons));
		win = lose = 0;
	}
} *root;

char s[maxn];
int n, k;

inline void insert(trie *node, char *s) {
	if(!*s) {
		return ;
	}
	int son = *s - 'a';
	if(!node->sons[son])
		node->sons[son] = new trie();
	insert(node->sons[son], s + 1);
}

inline void dfs(trie *node) {
	bool leaf = true;
	for(int i = 0 ; i < sigma ; ++ i)
		if(node->sons[i]) {
			leaf = false;
			dfs(node->sons[i]);
			node->win = (node->win | (!node->sons[i]->win));
			node->lose = (node->lose | (!node->sons[i]->lose));
		}
	if(leaf) {
		node->win = false;
		node->lose = true;
	}
}

int main () {
	#ifndef ONLINE_JUDGE
	freopen("456d.in", "r", stdin);
	freopen("456d.out", "w", stdout);
	#endif
	cin.sync_with_stdio(false);

	root = new trie();

	cin >> n >> k;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> s + 1;
		insert(root, s + 1);
	}
	dfs(root);
	if(!root->win) {
		cout << "Second\n";
	}	
	else {
		if(root->lose)
			cout << "First\n";
		else
			if(k % 2 == 0)
				cout << "Second\n";
			else
				cout << "First\n";
	}
}
