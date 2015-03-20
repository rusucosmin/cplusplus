#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const int maxn = 55;

int n, m, up[maxn][maxn], lf[maxn][maxn], cnt1, cnt2, match[maxn * maxn], pereche[maxn * maxn];
char s[maxn][maxn];
bitset <maxn * maxn> used;
vector <int> g[maxn * maxn];

inline bool pairup(int node) {
	if(used[node])
		return 0;
	used[node] = 1;
	for(auto it : g[node])
		if(!pereche[it]) {
			pereche[it] = node;
			match[node] = it;
			return 1;
		}
	for(auto it : g[node])
		if(pairup(pereche[it])) {
			pereche[it] = node;
			match[node] = it;
			return 1;
		}
	return 0;
}

inline int getmaxmatching() {
	int matching = 0;
	for(bool change = true ; change ; ) {
		change = false;
		used.reset();
		for(int i = 1 ; i <= cnt1 ; ++ i)
			if(!match[i] && pairup(i)) {
				++ matching;
				change = true;
			}
	}
	return matching;
}

int main() {
	ifstream fin("s013.in");
	ofstream fout("s013.out");

	fin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i)
		fin >> s[i] + 1;	
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= m ; ++ j)
			if(s[i][j] == '*') {
				if(s[i - 1][j] == '*')
					up[i][j] = up[i - 1][j];
				else
					up[i][j] = ++ cnt1;
				if(s[i][j - 1] == '*')
					lf[i][j] = lf[i][j - 1];
				else
					lf[i][j] = ++ cnt2;
				g[up[i][j]].push_back(lf[i][j]);
			}
	fout << getmaxmatching() << '\n';
}
