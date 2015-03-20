#include <fstream>
#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

const int maxn = 100005;

int n, a[maxn], aib[maxn], dp1[maxn], dp2[maxn], maxi;

inline int lsb(int x) {
	return x & (-x);
}

inline void update(int pos, int value) {
	for(int i = pos ; i <= maxi ; i += lsb(i)) 	
		if(aib[i] < value)
			aib[i] = value;
}

inline int query(int pos) {
	int maxp = 0;
	for(int i = pos ; i > 0 ; i -= lsb(i))
		if(aib[i] > maxp)
			maxp = aib[i];
	return maxp;
}

int fr[maxn];
char ans[maxn];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("486e.in", "r", stdin);
	freopen("486e.out", "w", stdout);
	#endif
	int lis = 1;
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> a[i];
		maxi = max(maxi, a[i]);
	}
	for(int i = 1 ; i <= n ; ++ i) {
		dp1[i] = query(a[i] - 1) + 1;
		lis = max(lis, dp1[i]);
		update(a[i], dp1[i]);
	}
	memset(aib, 0, sizeof(aib));
	reverse(a + 1, a + n + 1);
	for(int i = 1 ; i <= n ; ++ i)
		a[i] = -a[i] + maxi + 1;
	for(int i = 1 ; i <= n ; ++ i) {
		dp2[i] = query(a[i] - 1) + 1;
		update(a[i], dp2[i]);
		ans[i] = '1';
	}
	reverse(dp2 + 1, dp2 + n + 1);
	for(int i = 1 ; i <= n ; ++ i)
		if(dp1[i] + dp2[i] == lis + 1) {
			ans[i] = '2';
			++ fr[dp1[i]];
		}
	for(int i = 1 ; i <= n ; ++ i)
		if(ans[i] == '2' && fr[dp1[i]] == 1)
			ans[i] = '3';
	cout << ans + 1 << '\n';
}
