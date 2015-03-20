#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>

using namespace std;

const int sigma = 26;

struct trie {
	trie *sons[sigma];
	int cnt;
	int end;
	trie() {
		cnt = 0;
		memset(sons, 0, sizeof(sons));
	}
} *root;

inline void insert(trie *node, char *s) {
	if(!*s) {
		++ node->cnt;
		++ node->end;
		return ;
	}
	++ node->cnt;
	int son = *s - 'a';
	if(!node->sons[son])
		node->sons[son] = new trie();
	insert(node->sons[son], s + 1);
}

inline void remove(trie *&node, char *s) {
	if(!*s) {
		-- node->end;			
		-- node->cnt;
		return ;
	}
	int son = *s - 'a';
	-- node->cnt;
	remove(node->sons[son], s + 1);
	if(!node->sons[son]->cnt)
		node->sons[son] = NULL;
}

inline int find(trie *node, char *s) {
	if(!*s)
		return node->end;
	int son = *s - 'a';
	if(!node->sons[son])
		return 0;
	return find(node->sons[son], s + 1);
}

inline int prefix(trie *node, char *s) {
	if(!*s)
		return 0;
	int son = *s - 'a';
	if(!node->sons[son])
		return 0;
	return 1 + prefix(node->sons[son], s + 1);
}

char s[25];

int main() {
	ifstream fin("trie.in");
	ofstream fout("trie.out");
	root = new trie();
	int op;
	while(fin >> op >> s + 1) {
		if(op == 0)
			insert(root, s + 1);
		if(op == 1)
			remove(root, s + 1);
		if(op == 2)
			fout << find(root, s + 1) << '\n';
		if(op == 3)
			fout << prefix(root, s + 1) << '\n';
	}
}
