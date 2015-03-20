#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>

using namespace std;

ifstream fin("ssnd.in");
ofstream fout("ssnd.out");

const int maxn = 1000005;
const int mod = 9973;

vector <int> primes;
bitset <maxn> ciur;
int t;
long long n;

inline void buildsieve() {
	for(int i = 2 ; i < maxn ; ++ i)
		if(!ciur[i]) {
			primes.push_back(i);
			for(int j = i + i ; j < maxn ; j += i)
				ciur[j] = 1;	
		}
}

inline int lgpow(int a, int b) {
	int ans = 1;
	a %= mod;
	for( ; b ; b >>= 1) {
		if(b & 1)
			ans = (1LL * ans * a) % mod;
		a = (1LL * a * a) % mod;
	}
	return ans;
}

inline int invmod(int x) {
	return lgpow(x, mod - 2);	
}

inline void getans(long long n) {
	int nr = 1, sum = 1;
	for(int i = 0 ; i < primes.size() && 1LL * primes[i] * primes[i] <= n ; ++ i) {
		if(n % primes[i])
			continue;
		int exp = 0;
		while(n % primes[i] == 0) {
			++ exp;
			n /= primes[i];
		}
		nr = nr * (exp + 1);
		int first = (lgpow(primes[i], exp + 1) - 1 + mod) % mod;
		int second = invmod(primes[i] - 1);
		sum = (1LL * sum * first * second) % mod;
	}
	if(n > 1) {
		nr = nr * 2;
		int first = (lgpow(n, 2) - 1 + mod) % mod;
		int second = invmod(n - 1);
		sum = (1LL * sum * first * second) % mod;
	}
	fout << nr << ' ' << sum << '\n';
}

int main() {
	ifstream fin("ssnd.in");
	ofstream fout("ssnd.out");
	buildsieve();
	fin >> t;
	while(t --) {
		fin >> n;
		getans(n);
	}
}
