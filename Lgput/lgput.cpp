#include <iostream>
#include <fstream>

using namespace std;

const int mod = 1999999973;

int n, p;

inline int lgpow(int a, int b) {
	a %= mod;
	int ans = 1;
	for( ; b ; b >>= 1) {
		if(b & 1)
			ans = (1LL * ans * a) % mod;
		a = (1LL * a * a) % mod;
	}
	return ans;
}

int main() {
	ifstream fin("lgput.in");
	ofstream fout("lgput.out");

	fin >> n >> p;
	fout << lgpow(n, p) << '\n';
}
