#include <iostream>
#include <fstream>
#include <string.h>
#include <iostream>
#include <iomanip>

using namespace std;

const int maxlg = 100;
const int sigma = 26;

struct trie {
	trie *sons[sigma];
	int sons_cnt;
	int end_cnt;
	int sum_end;
	trie() {
		memset(sons, 0, sizeof(sons));
		sons_cnt = 0;
		end_cnt = 0;
	}
} *root;

char s[maxlg];
int n;

inline void insert(trie *node, char *s) {
	if(!*s) {
		++ node->end_cnt;
		return ;
	}
	int son = *s - 'a';
	if(!node->sons[son]) {
		node->sons[son] = new trie();
		++ node->sons_cnt;
	}
	insert(node->sons[son], s + 1);
}

inline int dfs(trie *node, int pressed, int aux) {
	if(!node)
		return 0;
	int ans = 0;
	if(node->end_cnt)
		ans = pressed;
	for(int i = 0 ; i < sigma ; ++ i)
		if(node->sons[i])
			if(node->sons_cnt == 1)
				ans += dfs(node->sons[i], pressed + (node->end_cnt >= 1), node->sons_cnt);
			else
				ans += dfs(node->sons[i], pressed + 1, node->sons_cnt);
	return ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("12526.in", "r", stdin);
	freopen("12526.out", "w", stdout);
	#endif
	cout << fixed << setprecision(2);
	while(cin >> n) {
		root = new trie();
		cin.get();
		for(int i = 0 ; i < n ; ++ i) {
			cin.getline(s, maxlg);
			insert(root, s);
		}
		int ans = 0;
		for(int i = 0 ; i < sigma ; ++ i)
			if(root->sons[i])
				ans += dfs(root->sons[i], 1, root->sons_cnt);
		cout << ((1.0*ans)/n) << '\n';
	}
}
