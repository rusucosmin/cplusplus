#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <math.h>

using namespace std;

const int maxn = 400005;

int n, indeg[maxn], m;
map<string, int> code;
map<int, string> decode;
char s[5];
vector <int> ans, g[maxn];

inline void euler(int stnode) {
	stack <int> st;
	st.push(stnode);
	while(!st.empty()) {
		int node = st.top();
		if(g[node].size()) {
			int newnode = g[node].back();
			g[node].pop_back();
			st.push(newnode);
		}
		else {
			st.pop();
			ans.push_back(node);
		}
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("508d.in", "r", stdin);
	freopen("508d.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		string a, b;
		cin >> s;
		a += s[0];
		a += s[1];
		b += s[1];
		b += s[2];
		if(!code[a]) {
			code[a] = ++ m;
			decode[m] = a;
		}
		if(!code[b]) {
			code[b] = ++ m;
			decode[m] = b;
		}
		g[code[a]].push_back(code[b]);
		++ indeg[code[b]];
	}

	int cnt = 0;
	int source = 1;
	for(int i = 1 ; i <= m ; ++ i) {
		if((int)(g[i].size()) > indeg[i]) {
			cnt += (g[i].size() - indeg[i]);
			if(cnt > 1) {
				cout << "NO\n";
				return 0;
			}
			source = i;
		}
	}
	euler(source);
	if((int)(ans.size()) <= n) {
		cout << "NO\n";
		return 0;
	}
	cout << "YES\n";
	string a = decode[ans.back()];
	ans.pop_back();
	while(ans.size()) {
		a += decode[ans.back()][1];
		ans.pop_back();	
	}
	cout << a << '\n';
}
