#include <fstream>

using namespace std;

int n, m, p;

inline int gcd(int x, int y) {
	if(!y)
		return x;
	return gcd(y, x % y);
}

inline int lgpow(int a, int b) {
	int ans = 1;
	for( ; b ; b >>= 1) {
		if(b & 1)
			ans = (1LL * ans * a) % p;
		a = (1LL * a * a) % p;
	}
	return ans;
}

int main() {
	ifstream fin("gcd.in");
	ofstream fout("gcd.out");
	int t;
	fin >> t;
	while(t--) {
		fin >> n >> m >> p;
		fout << lgpow(2, gcd(n, m)) - 1 << '\n';
	}
}
