#include <iostream>

using namespace std;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
	#endif

	int t;
	cin >> t;
	while(t --) {
		long long n1, n2;
		int m;
		cin >> n1 >> n2 >> m;
		long long n = min(n1, n2);
		long long finalSum = max(n1 - n2, n2 - n1);
		long long mSum = (1LL * m * (m + 1)) / 2;
		cout << finalSum + max(0LL, 2LL * (n - mSum)) << '\n';
	}
}
