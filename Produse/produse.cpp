#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int maxn = 200005;
const int mod = 1000000007;

int n, d, v[maxn], cnt[maxn], fact[maxn], invers[maxn];
int dp[maxn]; /// dp[i] = cate submultimi cu produsul i exista

inline int lgPow(int a, int b) {
	int ret = 1;
	for( ; b ; b >>= 1) {
		if(b & 1)
			ret = (1LL * ret * a) % mod;
		a = (1LL * a * a) % mod;
	}
	return ret;
}

inline int invmod(int n) {
	return lgPow(n, mod - 2);
}

inline int comb(int n, int k) {
	return (1LL * ((1LL * fact[n] * invers[(fact[n - k])] % mod) * invers[fact[k]])) % mod;
}

int main() {
	ifstream fin("produse.in");
	ofstream fout("produse.out");

	fin >> n >> d;
	fact[0] = 1;

	for(int i = 1 ; i < maxn ; ++ i) {
		fact[i] = (1LL * fact[i - 1] * i) % mod;
	}

	for(int i = 1 ; i < maxn ; ++ i) {
		invers[i] = invmod(i);
	}

	for(int i = 1 ; i <= n ; ++ i) {
		fin >> v[i];
		++ cnt[v[i]];
	}

	for(int i = 1 ; i <= d ; ++ i) {
		vector <pair<int, int> > lastdp;
		long long product = 1;
		for(int j = 1 ; j <= cnt[i] ; ++ j) {
			product = product * i;
			if(product > d)
				break;
			lastdp.push_back(make_pair(product, comb(cnt[i], j)));
//			cerr << cnt[i] << ' ' << j << ' ' << comb(cnt[i], j) << '\n';
	//		dp[product] += comb(cnt[i], j);
			for(int k = 1 ; k <= d / product ; ++ k) {
				lastdp.push_back(make_pair(k * product, dp[k]));
	//			dp[k * product] = (dp[k * product] + dp[k]) % mod;
			}
		}
		for(auto it : lastdp) {
			dp[it.first] = (dp[it.first] + it.second) % mod;
		}
	}

	long long ans = 0;
	for(int i = 1 ; i <= d ; ++ i) {
		ans = (ans + dp[i]) % mod;
	}
	fout << ans << '\n';
}
