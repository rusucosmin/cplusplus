#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>

using namespace std;

const int maxn = 105;

int a[maxn][maxn], n, m, father[maxn * maxn];

const int dx[] = { 0, 1, 0,-1};
const int dy[] = {-1, 0, 1, 0};

inline int getcode(int x, int y) {
	return x * (m + 2) + y;
}

inline int find(int x) {
	if(father[x] != x)
		father[x] = find(father[x]);
	return father[x];
}

inline bool check() {
/// sus, dreapta, jos, stânga
	for(int i = 1 ; i <= m ; ++ i) {
		if(!(a[1][i] & (1 << 3)))
			return 0;
		if(!(a[n][i] & (1 << 1)))
			return 0;
	}
	for(int i = 1 ; i <= n ; ++ i) {
		if(!(a[i][1] & (1 << 0)))
			return 0;
		if(!(a[i][m] & (1 << 2)))
			return 0;
	}
	map<pair<int, int>, bool> _hash;
	vector <pair<int, int> > edges;
//	set<pair<int, int> > edges;
	for(int i = 1 ; i <= n ; ++ i) {
		for(int j = 1 ; j <= m ; ++ j) {
			for(int d = 0 ; d < 4 ; ++ d) {
				pair<int, int> act = make_pair(getcode(i, j), getcode(i + dx[d], j + dy[d]));
				if(act.first > act.second)
					swap(act.first, act.second);
				if(a[i][j] & (1 << d)) {
					if(_hash[act])
						return 0;
					_hash[act] = 1;
				}
			}
		}
	}
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= m ; ++ j)
			for(int d = 0 ; d < 4 ; ++ d) {
				pair<int, int> act = make_pair(getcode(i, j), getcode(i + dx[d], j + dy[d]));
				if(act.first > act.second)
					swap(act.first, act.second);
				if(!(a[i][j] & (1 << d))) {
					if(!_hash[act]) {
						edges.push_back(act);
						_hash[act] = 1;
					}
				}
			}
	for(int i = 0 ; i < (n + 2) * (m + 2) ; ++ i)
		father[i] = i;
	if(edges.size() != n * m - 1)
		return 0;
	for(auto it : edges) {
		int tx = find(it.first);
		int ty = find(it.second);
		if(tx == ty)
			return 0;
		father[tx] = ty;
	}
	return  1;
}

int main() {
	ifstream fin("verlab.in");
	ofstream fout("verlab.out");

	int t;
	fin >> t;
	while(t -- ) {
		fin >> n >> m;
		for(int i = 1 ; i <= n ; ++ i)
			for(int j = 1 ; j <= m ; ++ j) {
				fin >> a[i][j];
			}
		fout << check() << '\n';
	}

}

