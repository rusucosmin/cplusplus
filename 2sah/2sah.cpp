#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>

using namespace std;

const int mod = 100003;

ifstream fin("p2sah.in");
ofstream fout("p2sah.out");

int sum[1005][2005];

inline int lgpow(int a, int b) {
	int ans = 1;
	for( ; b ; b >>= 1) {
		if(b & 1)
			ans = (1LL * ans * a) % mod;
		a = (1LL * a * a) % mod;
	}
	return ans;
}

inline int brute(int n, int k) {
	memset(sum, 0, sizeof(sum));
	sum[1][n + 1] = 1;	
	for(int i = 2 ; i <= n + 1 ; ++ i)
		for(int j = 1 ; j <= 2*n + 1 ; ++ j)
			sum[i][j] = (sum[i - 1][j - 1] + sum[i - 1][j] + sum[i - 1][j + 1]) % mod;
	int x = 1, y = k;
	int ret = 0;
	while(x <= n + 1 && y <= 2 * n + 1) {
		ret = (ret + sum[x][y]) % mod;
		++ x;
		y += 2;
	}
	return ret;
}

inline int multiply(int a[3][3], int b[3][3], int c[3][3]) {
	for(int i = 0 ; i < 3 ; ++ i)
		for(int j = 0 ; j < 3 ; ++ j)
			for(int k = 0 ; k < 3 ; ++ k)
				a[i][j] = (a[i][j] + 1LL * b[i][k] * c[k][j]) % mod;
}

inline void lgmultiply(int p) {
	int z[3][3] = {
		{1, 1, 0},
		{1, 0, 1},
		{1, 0, 0}
	};
	int ans[3][3] = {
		{1, 0, 0},
		{0, 1, 0},
		{0, 0, 1} 
	};
	int aux[3][3];
	for( ; p ; p >>= 1) {
		if(p & 1) {
			memset(aux, 0, sizeof(aux));
			multiply(aux, ans, z);
			memcpy(ans, aux, sizeof(aux));
		}
		memset(aux, 0, sizeof(aux));
		multiply(aux, z, z);
		memcpy(z, aux, sizeof(aux));
	}
	fout << (4LL*ans[0][0] + 2LL*ans[1][0] + ans[2][0]) % mod << '\n';
}

inline void doit(int n, int k) {
//	for(int i = 1 ; i <= 10 ; ++ i, cerr << '\n')
//		for(int k = 1 ; k <= i;  ++ k)
//			cerr << brute(i, k) << ' ';
	if(n <= 1000) {
		fout << brute(n, k) << '\n';
		return ;
	}
	int x = n - k + 1;
	if(x == 1)
		fout << "1\n";
	else if(x == 2)
		fout << "2\n";
	else if(x == 3)
		fout << "4\n";
	else
		lgmultiply(x - 3);
}

int main() {
	int p, n, k;
	fin >> p >> n >> k;
	if(p == 1)
		fout << lgpow(3, k - 1) << '\n';
	else
		doit(n, k);
}
