#include <iostream>

using namespace std;

int n, k, l, c, d, nl, np, p;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("151a.in", "r", stdin);
	freopen("151a.out", "w", stdout);
	#endif
	cin >> n >> k >> l >> c >> d >> p >> nl >> np;
	cout << (min((k * l) / nl, min(c * d, p / np))) / n << '\n';
}
