#include <iostream>
#include <fstream>

using namespace std;

int a[10];

int main() {
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	for(int i = 1 ; i <= 6 ; ++ i)
		cin >> a[i];
	int cnt = 2*a[1] + 1;
	long long sum = 0;
	for(int i = 1 ; i <= min(a[2], a[6]) ; ++ i) {
		sum += cnt;
		cnt += 2;
	}
	int aux = cnt - 1;
	cnt = 2*a[4] + 1;
	for(int i = 1 ; i <= min(a[3], a[5]) ; ++ i) {
		sum += cnt;
		cnt += 2;
	}
	int bux = cnt - 1;
	for(int i = min(a[2], a[6]) + 1 ; i <= max(a[2], a[6]) ; ++ i)
		sum += aux;
	cout << sum << '\n';
}
