#include <fstream>
#include <iostream>

using namespace std;

int a, b, c;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("479a.in", "r", stdin);
	freopen("479a.out", "w", stdout);
	#endif
	cin >> a >> b >> c;
	int ans = a * b * c;
	ans = max(ans, a + b + c);
	ans = max(ans, (a + b) * c);
	ans = max(ans, a * (b + c));
	cout << ans << '\n';
}
