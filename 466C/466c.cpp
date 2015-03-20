#include <iostream>

using namespace std;

const int maxn = 500005;

int n, a[maxn], sum[maxn];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("466c.in", "r", stdin);
	freopen("466c.out", "w", stdout);
	#endif
	long long s = 0;
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> a[i];
		s += a[i];
	}
	if(s % 3) {
		cout << "0\n";
		return 0;
	}
	long long aux = 0;
	for(int i = n ; i ; -- i) {
		aux += a[i];
		sum[i] = sum[i + 1] + (aux * 3 == s);
	}
	aux = 0;
	long long ans = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		aux += a[i];
		if(aux * 3 == s)
			ans = ans + sum[i + 2];
	}
	cout << ans << '\n';
}
