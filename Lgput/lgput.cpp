#include <iostream>
#include <fstream>

using namespace std;

const int mod = 1999999973;

inline int lgput(int a, int b) {
	a %= mod;
	int ret = 1;
	for( ; b ; b >>= 1) {
		if(b & 1)	
			ret = (1LL * ret * a) % mod;
		a = (1LL * a * a) % mod;
	}
	return ret;
}

int main() {
	int a, b;
	ifstream fin("lgput.in");
	ofstream fout("lgput.out");
	fin >> a >> b;
	fout << lgput(a, b) << '\n';
}
