#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

ll cnt[2], given[2], x, y;

inline bool check(ll values) {
	ll f[] = {values / x, values / y};
	ll xy = x * y;
	ll both = values / xy;
	f[0] -= both;
	f[1] -= both;
	ll others = values - f[0] - f[1] - both;
	ll tcnt[] = {max(0LL, cnt[0] - f[1]), max(0LL, cnt[1] - f[0])};
	return tcnt[0] + tcnt[1] <= others;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("483b.in", "r", stdin);
	freopen("483b.out", "w", stdout);
	#endif
	cin >> cnt[0] >> cnt[1] >> x >> y;
	ll li = 0, ls = (1LL << 62);
	ll ans = -1;
	while(li <= ls) {
		ll mid = ls - (ls - li) / 2;
		if(check(mid)) {
			ans = mid;
			ls = mid - 1;
		}
		else
			li = mid + 1;
	}
	cout << ans << '\n';
}
