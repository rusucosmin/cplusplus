#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

const int maxn = 50;
const int maxwords = 2000005;
const int sigma = 26;

int n, l;
char s[maxwords][maxn];

struct trie {
	trie *sons[sigma];
	int max1, max2, id;
	trie() {
		memset(sons, 0, sizeof(sons));
		max1 = max2 = 0;
	}
} *root;

inline void insert(trie *node, char *s, int pos) {
	if(pos == -1) {
		node->id = n;	
		return;
	}
	int son = *s - 'a';
	if(!node->sons[son])
		node->sons[son] = new trie();
	insert(node->sons[son], s, pos - 1);	
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("phryme.in", "r", stdin);
	freopen("phryme.out", "w", stdout);
	#endif

	root = new trie();

	while(cin.getline(s[++ n], maxn) && (l = strlen(s[n]))) {
		insert(root, s[n], l - 1);	
		cout << s[n] << '\n';
	}
	while(cin.getline(s[0], maxn)) {
		cout << s[0] << '\n';
	}
		
}
