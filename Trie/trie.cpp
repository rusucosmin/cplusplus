#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

const int sigma = 26;

int op;
char s[25];

struct trie {
	trie *sons[sigma];
	int cnt, sonscnt;
	trie () {
		cnt = 0;
		memset(sons, 0, sizeof(sons));
		sonscnt = 0;
	}
} *root = new trie();

inline void insert(trie *&node, char *s) {
	if(!*s) {
		++ node->cnt;
		return ;
	}
	int son = *s - 'a';
	if(!node->sons[son]) {
		++ node->sonscnt;
		node->sons[son] = new trie();
	}
	insert(node->sons[son], s + 1);
}

inline bool erase(trie *&node, char *s) {
	if(!*s) {
		-- node->cnt;
		if(!node->cnt && !node->sonscnt) {
			delete node;
			node = NULL; 
			return 1;
		}
		return 0;
	}
	int son = *s - 'a';
	if(erase(node->sons[son], s + 1)) {
		-- node->sonscnt;
		if(!node->sonscnt && !node->cnt) {
			delete node;
			node = NULL;
			return 1;
		}
	}
	return 0;
}

inline int find(trie *&node, char *s) {
	if(!*s)
		return node->cnt;
	int son = *s - 'a';
	if(!node->sons[son])
		return 0;
	return find(node->sons[son], s + 1);
}

inline int prefix(trie *&node, char *s) {
	if(!*s)
		return 0;
	int son = *s - 'a';
	if(!node->sons[son])
		return 0;
	return 1 + prefix(node->sons[son], s + 1);
}

int main() {
	ifstream fin("trie.in");
	ofstream fout("trie.out");
	
	while(fin >> op >> s) {
		if(op == 0)
			insert(root, s);
		if(op == 1)
			if(erase(root, s))
				root = new trie();
		if(op == 2)
			fout << find(root, s) << '\n';
		if(op == 3)
			fout << prefix(root, s) << '\n';
	}
}
