#include <iostream>
#include <fstream>

using namespace std;

const int maxn = 200005;

int n, a[maxn];
long long s, sum;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("534c.in", "r", stdin);
	freopen("534c.out", "w", stdout);
	#endif
	cin >> n >> s;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> a[i];
		sum += a[i];
	}
	for(int i = 1 ; i <= n ; ++ i) {
		long long acts = sum - a[i];
		long long aux = max(0LL, s - acts - 1);
		long long bux = max(0LL, a[i] - s + n - 1);
		cout << aux + bux << ' ';
	}
		
}
