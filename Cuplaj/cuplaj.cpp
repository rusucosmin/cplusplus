#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

const int maxn = 10005;

int n, m, e, cuplaj[maxn], _left[maxn];
vector <int> g[maxn];
bitset <maxn> used;

inline bool pairup(int node) {
	if(used[node])
		return false;
	used[node] = 1;
	for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
		if(!_left[*it] || pairup(_left[*it])) {
			cuplaj[node] = *it;
			_left[*it] = node;
			return true;
		}
	return false;
}

int main() {
	ifstream fin("cuplaj.in");
	ofstream fout("cuplaj.out");
	fin >> n >> m >> e;
	for(int i = 1 ; i <= e ; ++ i) {
		int x, y;
		fin >> x >> y;
		g[x].push_back(y);
	}
	int sz = 0;
	for(bool change = true ; change ; ) {
		change = false;
		used.reset();
		for(int i = 1 ; i <= n ; ++ i)
			if(!cuplaj[i])
				if(pairup(i)) {
					++ sz;
					change = true;
				}
	}
	fout << sz << '\n';
	for(int i = 1 ; i <= n ; ++ i)
		if(cuplaj[i])
			fout << i << ' ' << cuplaj[i] << '\n';
}
