#include <iostream>

using namespace std;

int main() {
	long long n;
	cin >> n;
	if(n & 1)
		cout << -1LL * (n + 1LL) / 2LL << '\n';
	else
		cout << n / 2LL << '\n';
}
