#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <iomanip>

using namespace std;

const int maxn = 505;

pair<int, int> x[maxn];
int s, n, father[maxn], t;
vector <pair<double, pair<int, int> > > edges;
vector <double> len;

inline double dist(pair<int, int> a, pair<int, int> b) {
	return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

inline int find(int x) {
	if(father[x] != x)
		father[x] = find(father[x]);
	return father[x];
}

inline bool unite(int x, int y) {
	x = find(x);
	y = find(y);
	if(x == y)
		return 0;
	father[x] = y;
	return 1;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uva-10369.in", "r", stdin);
	freopen("uva-10369.out", "w", stdout);
	#endif
	cin >> t;
	cout << fixed << setprecision(2);
	while(t --) {
		cin >> s >> n;
		for(int i = 1 ; i <= n ; ++ i) {
			cin >> x[i].first >> x[i].second;
			father[i] = i;
			for(int j = 1 ; j < i ; ++ j)
				edges.push_back(make_pair(dist(x[i], x[j]), make_pair(i, j)));
		}
		sort(edges.begin(), edges.end());
		for(int i = 0 ; len.size() != n - 1 ; ++ i)
			if(unite(edges[i].second.first, edges[i].second.second))
				len.push_back(edges[i].first);
		cout << len[n - 1 - s] << '\n';
		edges.clear();
		len.clear();
	}
}
