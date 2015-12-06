#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

const int maxn = 2000005;

char a[maxn], b[maxn];
int pi[maxn];

inline vector <int> kmp(char *a, char *b, int *pi) { /// searches for A in B
	vector <int> matches;
	int k = 0;
	int n = strlen(a + 1);
	int m = strlen(b + 1);
	for(int i = 2 ; i <= n ; ++ i) {
		while(k != 0 && a[k + 1] != a[i])
			k = pi[k];
		if(a[k + 1] == a[i])
			++ k;
		pi[i] = k;
	}
	k = 0;
	for(int i = 1 ; i <= m ; ++ i) {
		while(k != 0 && a[k + 1] != b[i])
			k = pi[k];
		if(a[k + 1] == b[i])
			++ k;
		if(k == n) {
			matches.push_back(i - n);
			k = pi[k];
		}
	}
	return matches;
}

inline vector <int> rabinkarp(char *a, char *b) {
	const int mod1 = 666013;
	const int mod2 = 100007;
	const int base = 72;
	int n = strlen(a + 1);
	int m = strlen(b + 1);
	int phash1 = 0, phash2 = 0, pow1 = 1, pow2 = 1;
	for(int i = 1 ; i <= n ; ++ i) {
		phash1 = (phash1 * base + a[i]) % mod1;
		phash2 = (phash2 * base + a[i]) % mod2;
		pow1 = (pow1 * base) % mod1;
		pow2 = (pow2 * base) % mod2;
	}
	vector <int> matches;
	if(m < n)
		return matches;
	int hash1 = 0, hash2 = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		hash1 = (hash1 * base + b[i]) % mod1;
		hash2 = (hash2 * base + b[i]) % mod2;
	}
	if(hash1 == phash1 && hash2 == phash2)
		matches.push_back(0);
	for(int i = n + 1 ; i <= m ; ++ i) {
		hash1 = (hash1 * base + b[i]) % mod1;
		hash2 = (hash2 * base + b[i]) % mod2;
		hash1 = (hash1 - (pow1 * (b[i - n])) % mod1 + mod1) % mod1;
		hash2 = (hash2 - (pow2 * (b[i - n])) % mod2 + mod2) % mod2;
		if(hash1 == phash1 && hash2 == phash2)
			matches.push_back(i - n);
	}
	return matches;
}

int main() {
	ifstream fin("strmatch.in");
	ofstream fout("strmatch.out");

	fin.getline(a + 1, maxn);
	fin.getline(b + 1, maxn);
//	vector <int> matches = kmp(a, b, pi);
	vector <int> matches = rabinkarp(a, b);
	fout << matches.size() << '\n';
	for(int i = 0 ; i < min(1000, int(matches.size())) ; ++ i)
		fout << matches[i] << ' ';
}
