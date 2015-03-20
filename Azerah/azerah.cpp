#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

const int maxn = 1000005;
const int mod = 1000000007;

int a[maxn], n, t, impar[maxn], par[maxn];

int main() {
	ifstream fin("azerah.in");
	ofstream fout("azerah.out");

	fin >> t;
	while(t -- ) {
		fin >> n;
		for(int i = 1 ; i <= n ; ++ i)
			fin >> a[i];
		if(a[1] % 2 == 0) {
			par[1] = 1;
			impar[1] = 0;
		}
		else {
			par[1] = 0;
			impar[1] = 1;
		}
		for(int i = 2 ; i <= n ; ++ i) {
			if(a[i] % 2 == 0) {
				impar[i] = (impar[i - 1] + impar[i - 1]) % mod;
				par[i] = (1 + par[i - 1] + par[i - 1]) % mod;
			}
			else {
				impar[i] = (1 + impar[i - 1] + par[i - 1]) % mod;
				par[i] = (par[i - 1] + impar[i - 1]) % mod;
			}
		}
		fout << par[n] << '\n';
	}
}
