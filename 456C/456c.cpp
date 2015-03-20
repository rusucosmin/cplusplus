#include <iostream> 
#include <vector>

using namespace std;

const int maxn = 100005;

int a[maxn], cnt[maxn], m, n;
long long dp[maxn];

int main() {
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> a[i];
		++ cnt[a[i]];
		m = max(m, a[i]);
	}
	dp[0] = 0;
	dp[1] = cnt[1];
	for(int i = 2 ; i <= m ; ++ i)
		dp[i] = max(dp[i - 1], dp[i - 2] + 1LL * cnt[i] * i);
	cout << dp[m] << '\n';
}
