#include <fstream>
#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

const int maxn = 5005;
const int MOD = 1000000007;

vector <int> g[maxn];
int n, m, out[maxn], in[maxn];
bitset <maxn> isprime;
vector <int> prime;

inline void getPrime() {
	for(int i = 2 ; i < maxn ; ++ i)
		if(!isprime[i]) {
			prime.push_back(i);
			for(int j = i + i ; j < maxn ; j += i)
				isprime[j] = 1;
		}
}

inline int getExp(int x, int N) {
	return (x + 1) / (n - x - 1);
}

inline int lgPow(int a, int b) {
	int ret = 1;
	for( ; b ; b >>= 1) {
		if(b & 1)
			ret = (1LL * ret * a) % MOD;
		a = (1LL * a * a) % MOD;
	}
	return ret;
}

int main() {
	ifstream fin("divisorgraph.in");
	ofstream fout("divisorgraph.out");
	int t;
	fin >> t;
	getPrime();
	while(t --) {
		memset(in, 0, sizeof(in));
		memset(out, 0, sizeof(out));
		for(int i = 1 ; i <= n ; ++ i)
			vector <int> ().swap(g[i]);
		fin >> n >> m;
		for(int i = 1 ; i <= m ; ++ i) {
			int x, y;
			fin >> x >> y;
			g[x].push_back(y);
			++ out[x];
			++ in[y];
		}
		vector <int> exp;
		for(int i = 1 ; i <= n ; ++ i)
			if(in[i] == 1)
				exp.push_back(getExp(out[i], n));
		sort(exp.begin(), exp.end(), greater<int>());
		int ans = 1;
		for(int i = 0 ; i < exp.size() ; ++ i)
			ans = (1LL * ans * lgPow(prime[i], exp[i])) % MOD;
		fout << ans << '\n';
	}
}
