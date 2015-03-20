#include <iostream>

using namespace std;

long long n, a, b;
bool swapped = false;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("466b.in", "r", stdin);
	freopen("466b.out", "w", stdout);
	#endif
	cin >> n >> a >> b;
	if(a * b >= 6 * n) {
		cout << a * b << '\n' << a << ' ' << b << '\n';
		return 0;
	}
	if(a > b) {
		swap(a, b);
		swapped = true;
	}
	long long ansa = 1000000008; long long ansb = 1000000008;
	for(long long i = a ; i * i <= 6 * n ; ++ i) {
		long long newb = 6 * n / i;
		while(newb * i < 6 * n)
			++ newb;
		if(newb < b)
			continue;
		if(ansa * ansb > newb * i) {
			ansa = i;
			ansb = newb;
		}
	}
	if(swapped)
		swap(ansa, ansb);
	cout << ansa * ansb << '\n' << ansa << ' ' << ansb << '\n';
}
