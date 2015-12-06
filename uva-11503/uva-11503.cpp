#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <map>

using namespace std;

const int maxn = 200005;

int father[maxn], n, sz[maxn], t;
map<string, int> mymap;

inline int find(int x) {
	if(father[x] != x)
		father[x] = find(father[x]);
	return father[x];
}

inline void unite(int x, int y) {
	x = find(x);
	y = find(y);
	if(x != y) {
		father[x] = y;
		sz[y] += sz[x];
	}
	cout << sz[y] << '\n';
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uva-11503.in", "r", stdin);
	freopen("uva-11503.out", "w", stdout);
	#endif
	cin >> t;
	while(t -- ) {
		mymap.clear();
		n = 0;
		int cnt;
		cin >> cnt;
		while(cnt --) {
			string a, b;
			cin >> a >> b;
			if(!mymap[a]) {
				mymap[a] = ++ n;
				father[n] = n;
				sz[n] = 1;
			}
			if(!mymap[b]) {
				mymap[b] = ++ n;
				father[n] = n;
				sz[n] = 1;
			}
			unite(mymap[a], mymap[b]);
		}
	}
	
}
