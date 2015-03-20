#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string.h>

using namespace std;

const int maxn = 10015;
const int sigma = 2;

char word[maxn], s[maxn];
int n, t, nodes, dp[maxn];

vector <string> morse = {
".-", "-...", "-.-.", "-..",
".", "..-.", "--.",  "....", 
"..", ".---", "-.-",  ".-..", 
"--", "-.", "---", ".--.", 
"--.-", ".-.",  "...",  "-", 
"..-", "...-", ".--",  "-..-", 
"-.--", "--.."
};

struct trie {
	trie *sons[sigma];
	int cnt;
	int matches;
	trie () {
		memset(sons, 0, sizeof(sons));
		cnt = ++ nodes;
		matches = 0;
	}
} *root;

inline int getnode(char s) {
	if(s == '.')
		return 0;
	return 1;
}

inline void insert(char *s) {
	trie *node = root;
	for( ; *s ; ++ s) {
		for(int j = 0 ; j < morse[*s - 'A'].size() ; ++ j) {
			if(!node->sons[getnode(morse[*s - 'A'][j])])
				node->sons[getnode(morse[*s - 'A'][j])] = new trie();
			node = node->sons[getnode(morse[*s - 'A'][j])];	
		}
	}
	++ node->matches;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("spoj-morse.in", "r", stdin);
	freopen("spoj-morse.out", "w", stdout);
	#endif
	cin >> t;
	while(t -- ) {
		nodes = 0;
		root = new trie();
		cin >> s + 1;
		cin >> n;
		while(n --) {
			cin >> word;
			insert(word);
		}
		n = strlen(s + 1);
		memset(dp, 0, sizeof(dp));
		dp[n + 1] = 1;
		for(int i = n ; i >= 1 ; -- i) {
			dp[i] = 0;
			trie *node = root;
			for(int j = i ; j <= n && node ; ++ j) {
				node = node->sons[getnode(s[j])];
				if(node && node->matches)
					dp[i] += node->matches * dp[j + 1];
			}
		}
		cout << dp[1] << '\n';

	}
	
}
