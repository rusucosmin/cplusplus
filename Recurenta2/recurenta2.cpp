#include <fstream>
#include <string.h>

using namespace std;

const int MOD = 666013;

inline void multiply(int a[7][7], int b[7][7], int c[7][7]) {
	for(int i = 0 ; i < 7 ; ++ i)
		for(int j = 0 ; j < 7 ; ++ j)
			for(int k = 0 ; k < 7 ; ++ k)
				c[i][j] = (c[i][j] + 1LL * a[i][k] * b[k][j]) % 666013;
}

inline void lgPow(int P, int c[7][7]) {
	int ans[7][7] = {
		{1, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 0, 1}
	};
	int aux[7][7];
	for( ; P ; P >>= 1) {
		if(P & 1) {
			memset(aux, 0, sizeof(aux));
			multiply(ans, c, aux);
			memcpy(ans, aux, sizeof(aux));
		}
		memset(aux, 0, sizeof(aux));
		multiply(c, c, aux);
		memcpy(c, aux, sizeof(aux));
	}
	memcpy(c, ans, sizeof(ans));
}

int main() {
	ifstream fin("recurenta2.in");
	ofstream fout("recurenta2.out");
	int A, B, C, x1, x2, N;
	fin >> A >> B >> C >> x1 >> x2 >> N;
	int c[7][7] = {
		{A, 1, 0, A, 1, 0, 0},
		{B, 0, 0, B, 0, 0, 0},
		{C, 0, 1, C, 0, 1, 0},
		{0, 0, 0, A, 1, 0, A},
		{0, 0, 0, B, 0, 0, B},
		{0, 0, 0, C, 0, 1, C},
		{0, 0, 0, 0, 0, 0 ,1}
	};
	lgPow(N - 2, c);
	int X[] = {x2, x1, 1, (3 * x2) % MOD, (3 * x1) % MOD, 3, (x1 + 2*x2) % MOD};
	int ans = 0;
	for(int i = 0 ; i < 7 ; ++ i)
		ans = (ans + 1LL * X[i] * c[i][6]) % MOD;
	fout << ans << '\n';
}
