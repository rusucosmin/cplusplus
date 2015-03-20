#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int maxn = 200005;

int a[maxn], b[maxn], n, m, pi[maxn];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("471d.in", "r", stdin);
	freopen("471d.out", "w", stdout);
	#endif
	cin >> n >> m;
	int last;
	cin >> last;
	for(int i = 2 ; i <= n ; ++ i) {
		int x;
		cin >> x;
		a[i - 1] = x - last;
		last = x;
	}
	cin >> last;
	for(int i = 2 ; i <= m ; ++ i) {
		int x;
		cin >> x;
		b[i - 1] = x - last;
		last = x;
	}
	int ans = 0;
	if(m == 1) {
		cout << n << '\n';
		return 0;
	}
	-- n; -- m;
	/*
	for(int i = 1 ; i <= n ; ++ i)
		cout << a[i] << ' ';
	cout << '\n';
	for(int i = 1 ; i <= m ; ++ i)
		cout << b[i] << ' ';
	*/
	int k = 0;
	for(int i = 2 ; i <= m ; ++ i) {
		while(k > 0 && b[k + 1] != b[i])
			k = pi[k];
		if(b[k + 1] == b[i])
			++ k;
		pi[i] = k;
	}
	k = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		while(k > 0 && b[k + 1] != a[i])
			k = pi[k];
		if(b[k + 1] == a[i])
			++ k;
		if(k == m) {
			++ ans;
			k = pi[k];
		}
	}
	cout << ans << '\n';
}
