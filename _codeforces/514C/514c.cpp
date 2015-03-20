#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <string.h>

using namespace std;

const int maxn = 300005;
const int mod = 666013;
const int sigma = 3;
const char delta = 'a';

int n, m;
char s[maxn];

struct node {
	node *sons[sigma];
	int endings;
	node () {
		endings = 0;	
		memset(sons, 0, sizeof(sons));
	}
} *root;

inline void insert(node *nod, char *s) {
	if(!*s) {
		++ nod->endings;
		return ;
	}
	int son = *s - delta;
	if(!nod->sons[son])
		nod->sons[son] = new node();
	insert(nod->sons[son], s + 1);
}

inline bool query(node *nod, char *s, int changes) {
	if(!nod)
		return false;
	if(!*s) {
		if(changes == 1)
			if(nod->endings)
				return true;
			else
				return false;
		else
			return false;
	}
	bool ret = query(nod->sons[*s - delta], s + 1, changes);
	if(changes == 0)
		for(int i = 0 ; i < sigma ; ++ i)
			if(*s - delta != i)
				ret |= query(nod->sons[i], s + 1, changes + 1);
	return ret;
}


int main() {
	#ifndef ONLINE_JUDGE
	freopen("514c.in", "r", stdin);
	freopen("514c.out", "w", stdout);
	#endif
	root = new node();
	cin >> n >> m;
	cin.get();
	for(int i = 1 ; i <= n ; ++ i) {
		cin.getline(s + 1, maxn);
		insert(root, s + 1);
	}
	for(int i = 1 ; i <= m ; ++ i) {
		cin.getline(s + 1, maxn);
		if(query(root, s + 1, 0))
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}
