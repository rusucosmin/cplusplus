#include <iostream>
#include <vector>

using namespace std;

inline long long gcd(long long x, long long y) {
	if(y == 0)
		return 0;
	return x / y + gcd(y, x % y);
}

int main ( ){
	#ifndef ONLINE_JUDGE
	freopen("527a.in", "r", stdin);
	freopen("527a.out", "w", stdout);
	#endif
	long long a, b;
	cin >> a >> b;
	cout << gcd(a, b) << '\n';
}
