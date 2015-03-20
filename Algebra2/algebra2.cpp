#include <fstream>

using namespace std;

const int mod = 1000000009;

long long n, x, y;

inline long long lgMult(long long a, long long b) {
	long long ans = 0;
	for( ; b ; b >>= 1) {
		if(b & 1)
			ans = (ans + a) % mod;
		a = (a + a) % mod;
	}
	return ans;
}

inline long long lgPow(long long a,long long b) {
	long long ans = 1;
	for( ; b ; b >>= 1) {
		if(b & 1)
			ans = lgMult(ans, a);
		a = lgMult(a, a); 
	}
	return ans;
}

int main() {
	ifstream fin("algebra2.in");
	ofstream fout("algebra2.out");

	fin >> n;
	x = n;
	y = n + 1;
	if(x % 2 == 0)
		x /= 2;
	else
		y /= 2;
	x = x % (mod - 1);
	y = y % (mod - 1);

	fout << lgPow(lgPow(n, x), y) << '\n';	
	

}
