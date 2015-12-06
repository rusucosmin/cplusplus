#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

const int maxtext = 1000005;
const int maxword = 10005;
const int maxn = 105;
const int sigma = 26;

char text[maxtext], word[maxword];
int n, ans[maxn];

struct trie {
	trie *sons[sigma];
	trie *fail;
	int cnt;
	vector <int> matches;
	trie () {
		memset(sons, 0, sizeof(sons));
		fail = NULL;
		cnt = 0;
		matches.clear();
	}
} *root;

vector <trie*> q;

inline void insert(trie *node, char *s, int ind) {
	if(!*s) {
		node->matches.push_back(ind);
		return ;
	}
	int son = *s - 'a';
	if(!node->sons[son])
		node->sons[son] = new trie();
	insert(node->sons[son], s + 1, ind);
}

inline void buildfails() {
	trie *node = root;
	node->fail = node;
	q.push_back(node);
	for(int i = 0 ; i < q.size() ; ++ i) {
		node = q[i];
		for(int son = 0 ; son < sigma ; ++ son)
			if(node->sons[son]) {
				trie *k = node->fail;
				while(k != root && !k->sons[son])
					k = k->fail;
				if(k->sons[son] != node->sons[son] && k->sons[son])
					k = k->sons[son];
				node->sons[son]->fail = k;
				q.push_back(node->sons[son]);
			}
	}
}

inline void match() {
	trie *k = root;
	for(int i = 0 ; text[i] ; ++ i) {
		int son = text[i] - 'a';
		while(k != root && !k->sons[son])
			k = k->fail;
		if(k->sons[son])
			k = k->sons[son];
		++ k->cnt;
	}
}

inline void antibfs() {
	for(int i = q.size() - 1 ; i >= 0 ; -- i) {
		trie *node = q[i];
		node->fail->cnt += node->cnt;
		for(auto it : node->matches)
			ans[it] = node->cnt;
	}
}

int main() {
	ifstream fin("ahocorasick.in");
	ofstream fout("ahocorasick.out");
	fin.getline(text, maxtext);
	fin >> n;
	fin.getline(word, maxword);
	root = new trie();
	for(int i = 1 ; i <= n ; ++ i) {
		fin.getline(word, maxword);
		insert(root, word, i);
	}
	buildfails();
	match();
	antibfs();
	for(int i = 1 ; i <= n ; ++ i)
		fout << ans[i] << '\n';
}
