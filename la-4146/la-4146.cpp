#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <iostream>

using namespace std;

const int maxn = 12;
const int oo = 0x3f3f3f3f;

int dp[1 << maxn][300][3], d[3][maxn], n, t;

inline int memo(int conf, int tmp, int last) {
	int &ret = dp[conf][tmp][last];
	if(ret != -1)
		return ret;
	ret = 0;
	for(int i = 0 ; i < n ; ++ i)
		if(!(conf & (1 << i))) {
			for(int j = 0 ; j < 3 ; ++ j) {
				if(last == j)
					continue;
				if(d[j][i] + tmp > 280)
					continue;
				ret = max(ret, 1 + memo(conf | (1 << i), tmp + d[j][i], j));
			}
		}
	return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("la-4146.in", "r", stdin);
	freopen("la-4146.out", "w", stdout);
	#endif
	cin >> t;
	while(t--) {
		cin >> n;
		for(int j = 0 ; j < 3 ; ++ j)
			for(int i = 0 ; i < n ; ++ i)
				cin >> d[j][i];
		memset(dp, -1, sizeof(dp));
		cout << max(memo(0, 0, 0), memo(0, 0, 1)) << '\n';
	}
}
