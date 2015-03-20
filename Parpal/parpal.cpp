#include <fstream>
#include <iostream>

using namespace std;

const int maxn = 1000005;
const int base = 31;
const int mod1 = 100007;
const int mod2 = 100021;

char s[maxn];

inline bool check(int x, int y) {
	int i = (x + y) / 2;
	int j = (x + y) / 2 + 1;
	while(i >= x && j <= y && s[i] == s[j]) {
		-- i;
		++ j;
	}
	if(i == x - 1 && j == y + 1)
		return 1;
	return 0;
}

int main() {
	ifstream fin("parpal.in");
	ofstream fout("parpal.out");
	int t, hash1, hash2, invhash1, invhash2, pow1, pow2, last, i, l;
	fin >> t;
	fin.get();
	while(t --) {
		fin.getline(s, maxn);	
		hash1 = hash2 = 0;
		invhash1 = invhash2 = 0;
		pow1 = pow2 = 1;
		last = -1;
		l = 0;
		for(i = 0 ; s[i] ; ++ i) {
			hash1 = (hash1 * base + s[i] - 'a') % mod1;
			invhash1 = (invhash1 + pow1 * (s[i] - 'a')) % mod1;
			pow1 = (pow1 * base) % mod1;
			pow2 = (pow2 * base) % mod2;
			++ l;
			if(hash1 == invhash1 && l % 2 == 0 && check(i - l + 1, i)) {
				hash1 = hash2 = invhash1 = invhash2 = 0;
				pow1 = pow2 = 1;
				last = i;
				l = 0;
			}
		}
		if(last == i - 1)
			fout << "DA\n";
		else
			fout << "NU\n";
	}
	
}
