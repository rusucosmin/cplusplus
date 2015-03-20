#include <fstream>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 100005;
const int sigma = 26;

struct node {
	node *sons[sigma], *suffix;
	int fr, len;
	bool used;
	bool used2;
	node(int _len) {
		memset(sons, 0, sizeof(sons));
		suffix = NULL;
		fr = 0;
		len = _len;
		used = false;
	}
} *root1, *root2, *maxsuff;

char s[maxn];

inline void addletter(int pos) {	
	node *cur = maxsuff;
	int curlen = 0, letter = s[pos] - 'a';
	while(true) {
		curlen = cur->len;
		if(pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])
			break;
		cur = cur->suffix;
	}

	if(cur->sons[letter]) {
		maxsuff = cur->sons[letter];
		return ;
	}

	maxsuff = new node(cur->len + 2);
	cur->sons[letter] = maxsuff;

	if(maxsuff->len == 1) {
		maxsuff -> suffix = root2;
		return ;
	}
	
	while(true) {
		cur = cur->suffix;
		curlen = cur->len;
		if(pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
			maxsuff->suffix = cur->sons[letter];
			break;
		}
	}
}

vector <node *> discovered;

inline void bfs() {
	discovered.push_back(root1);
	discovered.push_back(root2);
	root1->used = 1;
	root2->used = 1;
	node *act;
	for(int i = 0 ; i < discovered.size() ; ++ i) {
		act = discovered[i];
		for(int j = 0 ; j < sigma ; ++ j)
			if(act->sons[j] && !act->sons[j]->used) {
				discovered.push_back(act->sons[j]);	
				act->sons[j]->used = 1;
			}
	}
}

int main() {
	root1 = new node(-1);
	root2 = new node(0);

	root2->suffix = root1;
	
	maxsuff = root2;

	ifstream fin("pal2.in");
	ofstream fout("pal2.out");
	fin.getline(s, maxn);
	for(int i = 0 ; s[i] ; ++ i) {
		addletter(i);
		++ maxsuff->fr;
	}
	bfs();
	
	long long ans = 0;
	for(int i = discovered.size() - 1 ; i ; -- i) {
		maxsuff = discovered[i];
		if(maxsuff == root1 || maxsuff == root2)
			continue;
		if(!maxsuff)
			continue;
		ans = ans + 1LL * maxsuff->len * maxsuff->fr * maxsuff->fr;
		if(maxsuff->suffix)
			maxsuff->suffix->fr += maxsuff->fr;
	}
	fout << ans << '\n';
}
