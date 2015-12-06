#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

const int maxn = 100005;

int n, aib[maxn];
vector <pair<int, int> > v;

inline int lsb(int x) {
	return x & (-x);
}

inline void insert(int node, int value) {
	for(int i = node ; i <= n ; i += lsb(i))
		aib[i] = (aib[i] + value) % 9917;
}

inline int query(int node) {
	int sum = 0;
	for(int i = node ; i > 0 ; i -= lsb(i))
		sum = (sum + aib[i]) % 9917;
	return sum;
}

int main() {
	freopen("inv.in", "r", stdin);
	freopen("inv.out", "w", stdout);
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		int x;
		cin >> x;
		v.push_back(make_pair(x, i));
	}
	int ans = 0;
	sort(v.begin(), v.end(), greater<pair<int, int> > ());
	for(int i = 0 ; i < n ; ++ i) {
		ans = (ans + query(v[i].second)) % 9917;
		insert(v[i].second, 1);
	}
	cout << ans << '\n';
}
