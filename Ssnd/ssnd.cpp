#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

ifstream fin("ssnd.in");
ofstream fout("ssnd.out");

const int mod = 9973;
const int maxn = 1000005;

vector <int> primes;
bitset <maxn> used;

inline void buildciur() {
	for(int i = 2 ; i < maxn ; ++ i) {
		if(used[i])
			continue;
		primes.push_back(i);
		for(int j = i + i ; j < maxn ; j += i)
			used[j] = 1;
	}
}

inline int lgpow(int a, int b) {
	a %= mod;
	int ret = 1;
	for( ; b ; b >>= 1) {
		if(b & 1)
			ret = (ret * a) % mod;	
		a = (a * a) % mod;
	}
	return ret;
}

inline int invmod(int x) {
	return lgpow(x, mod - 2);
}

int main() {
	int t, n;
	buildciur();
	fin >> t;
	while(t -- ) {
		fin >> n;
		int number = 1, sum = 1;
		for(int i = 0 ; i < primes.size() && primes[i] * primes[i] <= n ; ++ i) {
			if(n % primes[i])
				continue;
			int _exp = 0;
			while(n % primes[i] == 0) {
				++ _exp;
				n /= primes[i];
			}
			number = (1LL * number * (_exp + 1)) % mod;
			int first = lgpow(primes[i], _exp + 1) - 1;
			if(first < 0)
				first += mod;
			int second = invmod(primes[i] - 1);
			sum = (1LL * sum * first * second) % mod;
		}
		if(n > 1) {
			number = (2LL * number) % mod;
			int first = lgpow(n, 2) - 1;
			if(first < 0)
				first += mod;
			int second = invmod(n - 1);
			sum = (1LL * sum * first * second) % mod;
		}
		fout << number << ' ' << sum << "\n";
	}
}
