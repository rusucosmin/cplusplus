#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

const int maxn = 30005;
const int maxs = 100005;
const int mod = 666013;

ifstream fin("icrisop.in");
ofstream fout("icrisop.out");

int dp[105], n, s;
int type[105];

int z[105][105], aux[105][105], ans[105][105];

/*
inline void multiply(int a[105][105], int b[105][105], int c[105][105]) {
	for(int i = 1 ; i <= 100 ; ++ i)
		for(int j = 1 ; j <= 100 ; ++ j)
			for(int k = 1 ; k <= 100 ; ++ k)
				a[i][j] = (a[i][j] + 1LL * b[i][k] * c[k][j]) % mod;
}
*/

inline int add(int x, int y) {
	x = x + y;
	if(x >= mod)
		x -= mod;
	return x;
}

inline void lgpow(int p) {
	for(int i = 1 ; i <= 100 ; ++ i) {
		ans[i][i] = 1;
		z[i][1] = type[i];
		z[i][i + 1] = 1;
	}
	for( ; p ; p >>= 1) {
		if(p & 1) {
			for(int i = 1 ; i <= 100 ; ++ i)
				for(int j = 1 ; j <= 100 ; ++ j) {
					aux[i][j] = 0;
					for(int k = 1 ; k <= 100 ; ++ k)	
						aux[i][j] = add(aux[i][j], (1LL * ans[i][k] * z[k][j]) % mod);
				}
			memcpy(ans, aux, sizeof(aux));
		}
		for(int i = 1 ; i <= 100 ; ++ i)
			for(int j = 1 ; j <= 100 ; ++ j) {
				aux[i][j] = 0;
				for(int k = 1 ; k <= 100 ; ++ k)
					aux[i][j] = add(aux[i][j], (1LL * z[i][k] * z[k][j]) % mod);
			}
		memcpy(z, aux, sizeof(aux));
	}
	int sum = 0;
	for(int i = 1 ; i <= 100 ; ++ i)
		sum = (sum + 1LL * dp[100 - i + 1] * ans[i][1]) % mod;
	fout << sum << '\n';
}

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void getint(int &x) {
	x = 0;
	while(!('0' <= buff[pos] && buff[pos] <= '9'))
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	while('0' <= buff[pos] && buff[pos] <= '9') {
		x = x * 10 + buff[pos] - '0';
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}
}

int main() {
	freopen("icrisop.in", "r", stdin);
	getint(n); getint(s);
	for(int i = 1 ; i <= n ; ++ i) {
		int x;
		getint(x);
		++ type[x];
	}
	dp[0] = 1;
	for(int i = 1 ; i <= 100 ; ++ i)
		for(int j = 1 ; j <= min(i, 100) ; ++ j)
			dp[i] = add(dp[i], (1LL * type[j] * dp[i - j]) % mod);
	if(s <= 100)
		fout << dp[s] << '\n';
	else
		lgpow(s - 100);
	return 0;
}
