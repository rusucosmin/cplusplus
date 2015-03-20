#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

const int sigma = 2;

struct trie {
	trie *sons[sigma];
	int cnt, sum;
	trie() {
		memset(sons, 0, sizeof(sons));
		cnt = 0;
		sum = 0;
	}
} *root = new trie();

inline void insert(trie *node, string s, int pos) {
	if(pos == s.size()) {
		node->cnt ++;
		node->sum ++;
		return; 
	}
	int son = s[pos] - '0';
	if(!node->sons[son])
		node->sons[son] = new trie();
	insert(node->sons[son], s, pos + 1);
	node->sum = 0;
	for(int i = 0 ; i < sigma ; ++ i)
		if(node->sons[i])
			node->sum += node->sons[i]->sum;
	node->sum += node->cnt;
}

inline int query(trie *node, string s, int pos) {
	if(s.size() == pos)
		return node->sum;
	int son = s[pos] - '0';
	if(node->sons[son])
		return node->cnt + query(node->sons[son], s, pos + 1);
	return node->sum;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("acmtju3166.in", "r", stdin);
	freopen("acmtju3166.out", "w", stdout);
	#endif
	int n, m;
	cin >> n >> m;
	for(int i = 0 ; i < n ; ++ i) {
		int x;
		cin >> x;
		string s = "";
		for(int j = 0 ; j < x ; ++ j) {
			int y;
			cin >> y;
			if(y == 1)
				s += "1";
			else
				s += "0";
		}
		insert(root, s, 0);
	}
	for(int j = 0 ; j < m ; ++ j) {
		int x;
		cin >> x;
		string s = "";
		for(int j = 0 ; j < x ; ++ j) {
			int y;
			cin >> y;
			if(y == 1)
				s += "1";
			else
				s += "0";
		}
		cout << query(root, s, 0) << '\n';
	}
}
