#include <fstream>
#include <algorithm>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

const int maxn = 21;
const int mod = 666013;

int dp[1 << maxn][maxn], a[maxn][maxn], n, m, nodes;

inline int getcode(int x, int y) {
	return x * m + y;
}

inline int gcd(int a, int b) {
	if(!a || !b)
		return max(a, b);
	return __gcd(a, b);
}

int main() {
	ifstream fin("android.in");
	ofstream fout("android.out");

	fin >> n >> m;

	for(int i = 0 ; i < n ; ++ i)
		for(int j = 0 ; j < m ; ++ j)
			for(int k = 0 ; k < n ; ++ k)
				for(int l = 0 ; l < m ; ++ l) {
					int	cmmdc = gcd(abs(i - k), abs(j - l));
					if(cmmdc == 0)
						continue;
					int x = i, y = j;
					for(int p = 1 ; p < cmmdc ; ++ p) {
						x -= (i - k) / cmmdc;
						y -= (j - l) / cmmdc;
						a[getcode(i, j)][getcode(k, l)] |= (1 << getcode(x, y));
					}
				}
	
	nodes = n * m;
	int lim = (1 << nodes);
	int ans = 0;

	for(int i = 0 ; i < nodes ; ++ i)
		dp[1 << i][i] = 1;
	

	for(int conf = 0 ; conf < lim ; ++ conf) {
		for(int i = 0 ; i < nodes ; ++ i) {
			if(conf & (1 << i)) {
				for(int j = 0 ; j < nodes ; ++ j) {
					if(i != j && (conf & (1 << j)))
						if((a[j][i] & conf) == a[j][i]) {
							dp[conf][i] = dp[conf][i] + dp[conf ^ (1 << i)][j];
							if(dp[conf][i] >= mod)
								dp[conf][i] -= mod;
						}
				}
				ans += dp[conf][i];
				if(ans >= mod)
					ans -= mod;
			}
		}
	}
	fout << ans << '\n';
		
}
