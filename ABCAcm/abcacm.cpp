#include <fstream>
#include <string.h>

using namespace std;

const int MOD = 9907;

int N, A, B, C, ans[4][4], aux[4][4], m[4][4], T;

void multiply(int a[4][4], int b[4][4], int c[4][4]) {
	for(int i = 0 ; i < 3 ; ++ i)
		for(int j = 0 ; j < 3 ; ++ j)
			for(int k = 0 ; k < 3 ; ++ k) 
				a[i][j] = (a[i][j] + b[i][k] * c[k][j]) % MOD;
}

void lgPow(int P) {
	ans[0][0] = ans[1][1] = ans[2][2] = 1;
	for( ; P ; P >>= 1) {
		if(P & 1) {
			memset(aux, 0, sizeof(aux));
			multiply(aux, m, ans); /// aux = m * n
			memcpy(ans, aux, sizeof(aux));
		}
		memset(aux, 0, sizeof(aux));
		multiply(aux, m, m);
		memcpy(m, aux, sizeof(aux));
	}
}

int main () {
	ifstream fin("abcacm.in");
	ofstream fout("abcacm.out");
	fin >> T;
	while (T --) {
		fin >> A >> B >> C >> N;
		m[0][1] = A;
		m[1][0] = 1;
		m[1][1] = B;
		m[2][1] = C;
		m[2][2] = 1;
		if(N <= 2) {
			fout << "0\n";
			continue;
		}
		lgPow(N - 2);
		fout << ans[2][1] << '\n';
		memset(ans, 0, sizeof(ans));
		memset(m, 0, sizeof(m));
	}
}
