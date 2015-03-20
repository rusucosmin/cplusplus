#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <fstream>
#include <unordered_map>

using namespace std;

const int sigma = 26;
const int maxn = 50;

struct trie {
	trie *sons[sigma];	
	int ind;
	trie () {
		memset(sons, 0, sizeof(sons));
		ind = -1;
	}
} *root;

string a, b;
vector <string> words;

inline void insert(trie *node, string s, int pos, int ind) {
	if(s.size() == pos) {
		if(node->ind == -1)
			node->ind = ind;
		return ;
	}
	int son = s[pos] - 'a';
	if(!node->sons[son])
		node->sons[son] = new trie();
	insert(node->sons[son], s, pos + 1, ind);
}

inline void dfs(trie *node) {
	if(node->ind != -1)
		cout << words[node->ind] << '\n';
	for(int i = 0 ; i < sigma ; ++ i)
		if(node->sons[i])
			dfs(node->sons[i]);
}

inline bool query(trie *node, string s, int pos) {
	if(pos == s.size()) {
		bool ret = false;
		for(int i = 0 ; i < sigma ; ++ i)
			if(node->sons[i])
				dfs(node->sons[i]), ret = true;
		return ret;
	}
	int son = s[pos] - 'a';
	if(!node->sons[son])
		return 0;
	return query(node->sons[son], s, pos + 1);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("spoj-dict.in", "r", stdin);
	freopen("spoj-dict.out", "w", stdout);
	#endif
	int n, m, test = 0;
	string s;
	cin >> n;
	root = new trie();
	for(int	i = 0 ; i < n ; ++ i) {
		cin >> s;
		words.push_back(s);
		insert(root, s, 0, i);
	}
	cin >> m;
	for(int i = 0 ; i < m ; ++ i) {
		cout << "Case #" << i + 1 << ":\n";
		cin >> s;
		if(!query(root, s, 0))
			cout << "No match.\n";
	}
}
