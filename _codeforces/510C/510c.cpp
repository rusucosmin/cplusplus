#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <bitset>
#include <string.h>
#include <queue>

using namespace std;

const int maxn = 105;
const int sigma = 26;

int n, lg[maxn], deg[sigma];
char s[maxn][maxn];
vector <int> g[sigma];
vector <int> discovered;
bitset <sigma> used;

inline int getfirstpos(int i, int j) {
	for(int pos = 1 ; pos <= min(lg[i], lg[j]) ; ++ pos)
		if(s[i][pos] != s[j][pos])
			return pos;
	return min(lg[i], lg[j]) + 1;
}

inline void tsort() {
	queue <int> q;
	for(int i = 0 ; i < sigma ; ++ i)
		if(!deg[i])
			q.push(i);
	vector <int> ans;
	while(!q.empty()) {
		int node = q.front();
		ans.push_back(node);
		q.pop();
		for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
			if(-- deg[*it] == 0)
				q.push(*it);
	}
	if(ans.size() != sigma) {
		cout << "Impossible\n";
		return ;
	}
	for(auto it : ans)
		cout << (char)(it + 'a');
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("510c.in", "r", stdin);
	freopen("510c.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> s[i] + 1;
		lg[i] = strlen(s[i] + 1);
	}
	for(int i = 1 ; i <= n ; ++ i) {
		for(int j = i + 1 ; j <= n ; ++ j) {
			int pos = getfirstpos(i, j);	
			if(pos == min(lg[i], lg[j]) + 1) {
				if(lg[i] > lg[j]) {
					cout << "Impossible\n";
					return 0;
				}
			}
			else {
				g[s[i][pos] - 'a'].push_back(s[j][pos] - 'a');
				++ deg[s[j][pos] - 'a'];
			}
		}
	}
	tsort();
}
