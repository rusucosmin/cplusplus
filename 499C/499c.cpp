#include <iostream>

using namespace std;

const int maxn = 305;

int  xa, ya, xb, yb, ans, n;

inline bool check(int a, int b, int c, int x, int y) {
	return (1LL * a * x + 1LL * b * y + c) > 0;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("499c.in", "r", stdin);
	freopen("499c.out", "w", stdout);
	#endif

	cin >> xa >> ya >> xb >> yb;
	cin >> n;
	for(int i = 0 ; i < n ; ++ i) {
		int a, b, c;
		cin >> a >> b >> c;
		if(check(a, b, c, xa, ya) != check(a, b, c, xb, yb))
			++ ans;
	}
	cout << ans << '\n';
}
