#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>

using namespace std;

const int maxn = 100005;

int n, p, dp[200][200];
char s[maxn];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("486c.in", "r", stdin);
	freopen("486c.out", "w", stdout);
	#endif
	cin >> n >> p >> (s + 1);
	for(char i = 'a' ; i <= 'z' ; ++ i)
		for(char j = i + 1 ; j <= 'z' ; ++ j)
			dp[i][j] = dp[j][i] = min(j - i, i + 26 - j);
	int mid = (n / 2);
	if(p > mid) {
		p = n - p + 1;
		reverse(s + 1, s + n + 1);
	}
	int mini = n + 1, maxi = -1;
	int ans = 0;
	for(int i = 1 ; i <= mid ; ++ i)
		if(s[i] != s[n - i + 1]) {
			ans += dp[s[i]][s[n - i + 1]];	
			mini = min(mini, i);
			maxi = max(maxi, i);
		}
	if(maxi == -1) {
		cout << "0\n";
		return 0;
	}
	if(maxi <= p)
		ans += p - mini;
	else
		if(p <= mini)
			ans += maxi - p;
		else
			ans += maxi - mini + min(p - mini, maxi - p);
	cout << ans << '\n';
}
