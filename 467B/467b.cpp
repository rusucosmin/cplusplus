#include <fstream>
#include <iostream>
#include <string>
//#include <algorithm>

using namespace std;

const int maxn = 1005;

int n, m, x[maxn], k;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("467b.in", "r", stdin);
	freopen("467b.out", "w", stdout);
	#endif

	cin >> n >> m >> k;
	for(int i = 1 ; i <= m + 1 ; ++ i)
		cin >> x[i];
	int ans = 0;
	for(int i = 1 ; i <= m ; ++ i)
		if(__builtin_popcount((x[i] ^ x[m + 1])) <= k)
			++ ans;
	cout << ans << '\n';
	
}
