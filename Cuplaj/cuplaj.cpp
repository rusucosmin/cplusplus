#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

ifstream fin("cuplaj.in");
ofstream fout("cuplaj.out");

const int maxn = 10005;

int n, m, e, _right[maxn], _left[maxn];
bitset <maxn> used;
vector <int> g[maxn];

inline bool pairup(int node) {
	if(used[node])
		return 0;
	used[node] = 1;
	for(auto it : g[node])
		if(!_left[it] || pairup(_left[it])) {
			_left[it] = node;
			_right[node] = it;
			return 1;
		}
	return 0;
}

int main() {
	fin >> n >> m >> e;
	for(int i = 1 ; i <= e ; ++ i) {
		int x, y;
		fin >> x >> y;
		g[x].push_back(y);
	}
	int ans = 0;
	for(bool change = true ; change ; ) {
		change = false;
		used.reset();
		for(int i = 1 ; i <= n ; ++ i)
			if(!_right[i] && pairup(i)) {
				++ ans;
				change = true;
			}
	}
	fout << ans << '\n';
	for(int i = 1 ; i <= n ; ++ i)
		if(_right[i])
			fout << i << ' ' << _right[i] << '\n';
}
