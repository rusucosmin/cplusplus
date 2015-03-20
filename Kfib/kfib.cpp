#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

ifstream fin("kfib.in");
ofstream fout("kfib.out");

const int mod = 666013;

int Z[2][2] = {
	{0, 1},
	{1, 1}
};

inline void multiply(int a[2][2], int b[2][2], int c[2][2]) {
	for(int i = 0 ; i < 2 ; ++ i)
		for(int j = 0 ; j < 2 ; ++ j)
			for(int k = 0 ; k < 2 ; ++ k)
				a[i][j] = (a[i][j] + 1LL * b[i][k] * c[k][j]) % mod;
}

inline int kfib(int n) {
	int ans[2][2] = {
		{1, 0},
		{0, 1}
	};
	int aux[2][2];
	-- n;
	for( ; n ; n >>= 1) {
		if(n & 1) {
			memset(aux, 0, sizeof(aux));
			multiply(aux, ans, Z);
			memcpy(ans, aux, sizeof(aux));
		}
		memset(aux, 0, sizeof(aux));
		multiply(aux, Z, Z);
		memcpy(Z, aux, sizeof(aux));
	}
	return ans[1][1];
}

int main() {
	int n;
	fin >> n;
	fout << kfib(n) << '\n';
}
