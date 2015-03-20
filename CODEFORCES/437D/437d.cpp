#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 100005;

int n, m, father[maxn], s[maxn], a[maxn];
vector <pair<int, pair<int, int> > > v;
long long ans;

inline int find(int x) {
	if(father[x] != x)
		father[x] = find(father[x]);
	return father[x];
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("437d.in", "r", stdin);
	freopen("437d.out", "w", stdout);
	#endif
	cin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> a[i];
		father[i] = i;
		s[i] = 1;
	}
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		cin >> x >> y;
		v.push_back(make_pair(min(a[x], a[y]), make_pair(x, y)));
	}
	sort(v.begin(), v.end());
	reverse(v.begin(), v.end());
	for(int i = 0 ; i < v.size() ; ++ i) {
		int x = find(v[i].second.first);
		int y = find(v[i].second.second);
		int z = v[i].first;
		if(x == y)
			continue;
		father[x] = y;
		ans += (1LL * s[x] * s[y] * z);
		s[y] += s[x];
	}
	cout << (2.0 * ans) / (1LL * (n - 1) * n) << '\n';
}
