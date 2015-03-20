#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 300005;

int n, a[maxn];

int main() {
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> a[i];
	sort(a + 1, a + n + 1);
	long long ans = 1LL * n * a[n];
	for(int i = 1 ; i < n ; ++ i)
		ans += 1LL * (i + 1) * a[i];
	cout << ans << '\n';
}
