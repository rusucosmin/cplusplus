#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

const int maxn = 100005;
const int maxlg = 20;
const int mod = 666013;

int n, a[maxn], lg[maxn], rmq[maxlg][maxn];
unordered_map<int, vector <int> > _hash;

inline int gcd(int a, int b) {
	if(!b)
		return a;
	return gcd(b, a % b);
}

inline int query(int x, int y) {
	int len = y - x;
	int l = lg[len];
	int ans = rmq[l][x];
	ans = gcd(ans, rmq[l][y - (1 << l) + 1]);
	return ans;
}

inline int getans(vector <int> ind, int x, int y) {
	if(ind.size() == 0)
		return 0;
	int last = upper_bound(ind.begin(), ind.end(), y) - ind.begin();
	int first = lower_bound(ind.begin(), ind.end(), x) - ind.begin() + 1; 
	return last - first + 1;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("474f.in", "r", stdin);
	freopen("474f.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> a[i];
		rmq[0][i] = a[i];
		_hash[a[i]].push_back(i);
	}
	for(int i = 2 ; i <= n ; ++ i)
		lg[i] = lg[i >> 1] + 1;
	for(int l = 1 ; (1 << l) <= n ; ++ l) {
		int aux = (1 << (l - 1));
		for(int i = 1 ; i + (1 << l) - 1 <= n ; ++ i)
			rmq[l][i] = gcd(rmq[l - 1][i], rmq[l - 1][i + aux]);
	}
	int t;
	cin >> t;
	for(int i = 1 ; i <= t ; ++ i) {
		int x, y;
		cin >> x >> y;
		int _gcd = query(x, y);
		cout << y - x + 1 - getans(_hash[_gcd], x, y) << '\n';
	}
}
