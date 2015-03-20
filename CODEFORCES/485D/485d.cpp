#include <iostream>
#include <vector>
#include <string.h>
#include <bitset>

using namespace std;

const int maxn = 200005;
const int maxvalue = maxn * 10;

int n, v[maxvalue], m;
bitset <maxvalue> used;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("485d.in", "r", stdin);
	freopen("485d.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		int x;
		cin >> x;
		used[x] = 1;
		m = max(m, x);
	}
	int last = 0;
	for(int i = 1 ; i <= 2*m ; ++ i) {
		v[i] = last;
		if(used[i])
			last = i;
	}
	int ans = 0;
	for(int i = 1 ; i <= m ; ++ i)
		if(used[i])
			for(int j = 2 * i ; j <= 2*m ; j += i)
				ans = max(ans, v[j] % i);
	cout << ans << '\n';
}
