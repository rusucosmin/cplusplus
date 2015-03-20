#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

const int maxn = 100005;

long long a[maxn], dp[maxn];
long long ans;
int n, w;
long long m;

inline bool check(long long minvalue) {
	memset(dp, 0, sizeof(dp));

	/// dp[i] = number of segments starting at i'th index

	long long actint = 0;
	long long totalsegments = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		if(i > w)
			actint -= dp[i - w];
		if(a[i] + actint < minvalue) {
			dp[i] = (minvalue - a[i] - actint);
			actint += dp[i];
			totalsegments += dp[i];
		}
		if(totalsegments > m)
			return false;
	}
	return totalsegments <= m;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("460c.in", "r", stdin);
	freopen("460c.out", "w", stdout);
	#endif
	cin >> n >> m >> w;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> a[i]; 
	ans = *min_element(a + 1, a + n + 1);
	
	long long st = 1, dr = 1000000000000000LL;
	while(st <= dr) {
		long long mid = (st + (dr - st) / 2);
		if(check(mid)) {
			st = mid + 1;
			ans = mid;
		}
		else
			dr = mid - 1;
	}
	cout << ans << '\n';
}
