#include <iostream>
#include <fstream>
#include <algorithm>


using namespace std;

const int maxn = 250005;

int a[maxn], n;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("acmtimus1306.in", "r", stdin);
	freopen("acmtimus1306.out", "w", stdout);
	#endif

	cin >> n;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> a[i];
	if(n % 2 == 1) {
		int middle = (n + 1) / 2;
		nth_element(a + 1, a + middle, a + n + 1);
		cout << a[middle] << '\n';
	}
	else {
		int middle = n / 2;
		nth_element(a + 1, a + middle, a + n + 1);
		long long sum = a[middle];
		nth_element(a + 1, a + middle + 1, a + n + 1);
		sum = sum + a[middle + 1];
		if(sum % 2 == 0)
			cout << sum / 2 << '\n';
		else
			cout << sum / 2 << ".5\n";
	}
}
