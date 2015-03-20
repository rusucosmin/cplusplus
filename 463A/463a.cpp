#include <iostream>

using namespace std;

const int maxn = 105;

int a[maxn], n, s;

int main() {
	cin >> n >> s;
	s *= 100;
	int ans = -1;
	for(int i = 1 ; i <= n ; ++ i) {
		int x, y;
		cin >> x >> y;
		x = x * 100 + y;
		if(s >= x)
			ans = max(ans, (s - x) % 100);
	}
	cout << ans << '\n';
}
