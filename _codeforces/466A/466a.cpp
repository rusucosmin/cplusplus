#include <iostream>

using namespace std;

int main() {
	int n, m, a, b;
	cin >> n >> m >> a >> b;
	if(m * a > b) {
		int howmany = n / m;
		int rest = n % m;
		if(rest * a < b)
			cout << howmany * b + rest * a << '\n';
		else
			cout << howmany * b + b << '\n';
	}
	else
		cout << n * a << '\n';
}
