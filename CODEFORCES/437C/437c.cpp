#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

const int maxn = 1005; 

int n, m, a[maxn], ind[maxn];
bitset <maxn> used;
vector <int> g[maxn];

struct classcomp {
	inline bool operator () (const int & i, const int & j) const {
		return a[i] > a[j];
	}
};

int main() {
	#ifndef ONLINE_JUDGE
	freopen("437c.in", "r", stdin);
	freopen("437c.out", "w", stdout);
	#endif
	cin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> a[i];
		ind[i] = i;
	}
	sort(ind + 1, ind + n + 1, classcomp());
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	long long cost = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		int node = ind[i];
		used[node] = 1;
		for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
			if(!used[*it])
				cost += a[*it];
	}
	cout << cost << '\n';
}
