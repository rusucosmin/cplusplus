#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

const int maxn = 500005;
const int sigma = 26;

struct node {
	node *sons[sigma], *suffix;
	int fr, len, ans;
	node(int _len) {
		memset(sons, 0, sizeof(sons));
		len = _len;
		fr = 0;
	}
} *root1, *root2, *maxsuffix;

vector <node *> discovered;


inline void addletter(int pos, char *s) {
	node *act = maxsuffix;
	int actlen = 0, letter = s[pos] - 'a';

	while(true) {
		actlen = act->len;
		if(pos - 1 - actlen >= 0 && s[pos - 1 - actlen] == s[pos])
			break;	
		act = act->suffix;
	}

	if(act->sons[letter]) {
		maxsuffix = act->sons[letter];
		return ;
	}

	maxsuffix = new node(act->len + 2);;
	act->sons[letter] = maxsuffix;

	discovered.push_back(maxsuffix);

	if(maxsuffix->len == 1) {
		maxsuffix->suffix = root2;
		return ;
	}
	
	while(true) {
		act = act->suffix;
		actlen = act->len;
		if(pos - 1 - actlen >= 0 && s[pos - 1 - actlen] == s[pos]) {
			maxsuffix->suffix = act->sons[letter];
			break;
		}
	}
}

inline void check(int pos, char *s) {
	node *act = maxsuffix;
	int actlen, letter = s[pos] - 'a';

	while(true) {
		actlen = act->len;
		if(pos - 1 - actlen >= 0 && s[pos - 1 - actlen] == s[pos])
			break;
		act = act->suffix;
	}

	if(act->sons[letter]) {
		maxsuffix = act->sons[letter];
		return;
	}

	maxsuffix = new node(act->len + 2);
	act->sons[letter] = maxsuffix;

	if(maxsuffix->len == 1) {
		maxsuffix->suffix = root2;
		return ;	
	}

	while(true) {
		act = act->suffix;
		actlen = act->len;
		if(pos - 1 - actlen >= 0 && s[pos - 1 - actlen] == s[pos]) {
			maxsuffix->suffix = act->sons[letter];
			break;
		}
	}
}

char s[maxn], p[maxn];

int main() {
	ifstream fin("unicat.in");
	ofstream fout("unicat.out");

	fin.getline(s, maxn);
	fin.getline(p, maxn);

	root1 = new node(-1);
	root2 = new node(0);

	root2->suffix = root1;

	maxsuffix = root2;

	for(int i = 0 ; s[i]  ; ++ i) {
		addletter(i, s);
		maxsuffix->fr = 1;
	}

	for(int i = discovered.size() - 1 ; i >= 0 ; -- i) {
		maxsuffix = discovered[i];			
		if(maxsuffix->fr == 1)
			maxsuffix->suffix->fr = 1;
	}

	maxsuffix = root2;

	for(int i = 0 ; p[i] ; ++ i) {
		check(i, p);
		maxsuffix->ans = 2;
	}

	int ans = 0;
	for(int i = discovered.size() - 1 ; i >= 0 ; -- i) {
		maxsuffix = discovered[i];
		if(maxsuffix->ans == 2 && maxsuffix->fr == 1)
			++ ans;
		if(maxsuffix->ans == 2)
			maxsuffix->suffix->ans = 2;
	}
	fout << ans << '\n';
}
