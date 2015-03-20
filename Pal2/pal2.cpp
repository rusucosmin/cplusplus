#include <fstream>
#include <iostream>
#include <string.h>
#include <unordered_map>

using namespace std;

const int sigma = 27;
const int maxn = 100005;

struct trie {
	trie *sons[sigma];
	trie *father;
	int cnt;
	trie() {
		memset(sons, 0, sizeof(sons));
		cnt = 0;
	}
} *root, *node;

char a[maxn], b[maxn << 1];
int n, m, p[maxn << 1];
unordered_map<int, trie* > where;

inline void addson(trie *& node, char x) {
	if(!node->sons[x - 'a']) {
		node->sons[x - 'a'] = new trie();
		node->sons[x - 'a']->father = node;
	}
}

long long ans = 0;

inline void dfs(trie *node, int letters, int last) {
	for(int i = 0 ; i < sigma ; ++ i)
		if(node->sons[i]) {
			dfs(node->sons[i], letters + (i != (sigma - 1)), i);
			node->cnt +=  node->sons[i]->cnt;
		}
	if(last == (sigma - 1))
		return ;
	ans += 1LL * (letters * 2 - 1) * node->cnt * node->cnt;
}

inline void dfs2(trie *node, int letters, int last) {
	for(int i = 0 ; i < sigma; ++ i) {
		if(node->sons[i]) {
			dfs2(node->sons[i], letters + (i != (sigma - 1)), i);
			node->cnt += node->sons[i]->cnt;
		}
	}
	if(last == (sigma - 1))
		return;
	ans += 1LL * (letters * 2) * node->cnt * node->cnt;
}

int main() {
	ifstream fin("pal2.in");
	ofstream fout("pal2.out");

	root = new trie();
	root->father = root;

	fin.getline(a + 1, maxn);	
	n = strlen(a + 1);
	b[++ m] = ('z' + 1);
	for(int i = 1 ; i <= n; ++ i) {
		b[++ m] = a[i];
		b[++ m] = 'z' + 1;
	}
	for(int i = 1 ; i <= m ; ++ i) {
		addson(root, b[i]);
		where[i] = root->sons[b[i] - 'a'];
	}
	int best = 0, ind = 0;	
	for(int i = 1 ; i <= m ; ++ i) {
		if(i <= best) {
			where[i] = where[2 * ind - i];
			int aux = p[2 * ind - i];
			while(best - i < aux) {
			//	if(!where[i])
			//		break;
				where[i] = where[i]->father;
				-- aux;
			}
			p[i] = min(best - i, p[2 * ind - i]);
		}
		while(i - p[i] - 1 >= 1 && i + p[i] + 1 <= m && b[i - p[i] - 1] == b[i + p[i] + 1] ) {
			addson(where[i], b[i + p[i] + 1]);
			where[i] = where[i] -> sons[b[i + p[i] + 1] - 'a'];
			++ p[i];
		}
		++ where[i] -> cnt;
		if(i + p[i] > best) {
			best = i + p[i];
			ind = i;
		}
	}
	for(int i = 0 ; i + 1 < sigma ; ++ i)
		if(root->sons[i])
			dfs(root->sons[i], 1, i);
	if(root->sons[sigma - 1])
		dfs2(root->sons[sigma - 1], 0, sigma - 1);
	fout << ans << '\n';
}
