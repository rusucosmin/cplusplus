#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

const int maxn = 1005;
const int sigma = 26;

int t, n;
char s[maxn];

struct trie {
	trie *sons[sigma];	
	int cnt, sum;
	trie () {
		memset(sons, 0, sizeof(sons));
		cnt = 0;
		sum = 0;
	}
} *root;

inline void insert(trie *node, char *s) {
	if(!*s) {
		++ node->cnt;
		++ node->sum;
		return ;
	}
	int son = *s - 'a';
	if(!node->sons[son])
		node->sons[son] = new trie();
	insert(node->sons[son], s + 1);
	++ node->sum;
}

inline int getsum(trie *node, int level) {
	if(!node)
		return 0;
	if(node->sum == 1)
		return level;
	int ret = 0;
	for(int i = 0 ; i < sigma ; ++ i)
		if(node->sons[i])
			ret += getsum(node->sons[i], level + 1);
	return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("12506.in", "r", stdin);
	freopen("12506.out", "w", stdout);
	#endif
	cin >> t;
	while(t --) {
		root = new trie();
		cin >> n;
		cin.get();
		for(int i = 0 ; i < n ; ++ i) {
			cin.getline(s, maxn);
			insert(root, s);
		}
		cout << getsum(root, 0) << '\n';
	}
}
