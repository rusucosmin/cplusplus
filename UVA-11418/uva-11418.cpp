#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <bitset>
#include <string>
#include <cassert>

using namespace std;

const int maxn = 30;
const int sigma = 26;

int t, n, match[maxn], pereche[maxn];
string names[maxn][maxn];
vector <int> g[maxn];
bitset <maxn> used;

inline int getfirst(char s) {
	if('a' <= s && s <= 'z')
		return s - 'a' + 1;
	return s - 'A' + 1;
}

inline bool pairup(int node) {
	if(used[node])
		return 0;
	used[node] = 1;
	for(auto it : g[node])
		if(!pereche[it] || pairup(pereche[it])) {
			pereche[it] = node;
			match[node] = it;
			return 1;
		}
	return 0;
}

inline void word(string s) {
	s[0] = toupper(s[0]);
	cout << s[0];
	for(int i = 1 ; i < s.size() ; ++ i)
		cout << (char)tolower(s[i]);
	cout << '\n';
}

int test;

inline void matching() {
	int ans = 0;
	for(bool change = true ; change ; ) {
		change = false;
		used.reset();
		for(int i = 1 ; i <= n ; ++ i)
			if(!match[i] && pairup(i)) {
				++ ans;
				change = true;
			}
	}
	assert(ans == n);
	cout << "Case #" << ++ test << ":\n";
	for(int i = 1 ; i <= n ; ++ i)
		word(names[match[i]][i]);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uva-11418.in", "r", stdin);
	freopen("uva-11418.out", "w", stdout);
	#endif
	cin >> t;
	while(t -- ) {
		cin >> n;
		cerr << n << '\n';
		for(int i = 1 ; i <= n ; ++ i) {
			int cnt;
			cin >> cnt;
			cerr << cnt << ' ';
			while(cnt--) {
				string s;
				cin >> s;
				cerr << s << ' ';
				cerr << getfirst(s[0]) << '\n';
				if(getfirst(s[0]) > n)
					continue;
				names[i][getfirst(s[0])] = s;
				g[getfirst(s[0])].push_back(i);
			}
		}
		matching();
		for(int i = 1 ; i <= sigma ; ++ i)
			vector <int> ().swap(g[i]);
		memset(match, 0, sizeof(match));
		memset(pereche, 0, sizeof(pereche));
	}
	
}
