#include <fstream>
#include <stdio.h>
#include <vector>

using namespace std;

const int MAXP = 100010;

int fact[MAXP], invmod[MAXP];
long long a, b;
int p, q;

inline void gcd(int a, int b, int &x, int &y) {
	if(b == 0) {
		x = 1;
		y = 0;
		return;
	}
	int x0, y0;
	gcd(b, a % b, x0, y0);
	x = y0;
	y = x0 - (a / b) * y0;
}

inline int getComb(long long a, long long b) {
	vector <int> m, n;
	if(a < b)
		return 0;
	if(a == b)
		return 1;
	int ret = 1;
	while(a > 0 && b > 0) {
		int n = a % p;
		a /= p;
		int k = b % p;
		b /= p;
		if(n < k)
			return 0;
		ret = (1LL * ret * (1LL * fact[n] * (1LL * invmod[k] * invmod[n - k]) % p) % p) % p;
	}
	return ret;
}

int main() {
	ifstream fin("jap2.in");
	ofstream fout("jap2.out");
	fin >> p >> q;
	fact[0] = 1;
	invmod[0] = 1;
	for(int i = 1 ; i <= p ; ++ i) {
		int x, y;
		fact[i] = ((1LL * fact[i - 1] * i) % p);
		gcd(fact[i], p, x, y);
		if(x < 0)
			x = p + x % p;
		invmod[i] = x; 
	}
	while (q --) {
		fin >> a >> b;
		fout << getComb(a, b) << '\n';
	}
	
}
