#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <bitset>
#include <vector>

using namespace std;

const int maxn = 20005;
const int sigma = 26;
const int base = 36;
const int base2 = 27;
const int mod = 666013;
const int mod2 = 1000000007;

int n, m;
unordered_map<int, bool> _hash, _hash2;
vector <int> smt(sigma);

int main() {
	ifstream fin("criptare2.in");
	ofstream fout("criptare2.out");
		
	fin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		int thishash = 0, cnt = 0;
		int secondhash = 0;
		fill(smt.begin(), smt.end(), 0);
		string s;
		fin >> s;
		for(auto it:s) {
			if(smt[it - 'a'] == 0)
				smt[it - 'a'] = ++ cnt;
			thishash = (thishash * base + smt[it - 'a']) % mod;
			secondhash = (secondhash * base2 + smt[it - 'a']) % mod2;
		}
		_hash[thishash] = true;
		_hash2[secondhash] = true;
	}
	fin >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		string s;
		fin >> s;
		int thishash = 0, cnt = 0, secondhash = 0;
		fill(smt.begin(), smt.end(), 0);
		for(auto it:s) {
			if(smt[it - 'a'] == 0)
				smt[it - 'a'] = ++ cnt;
			thishash = (thishash * base + smt[it - 'a']) % mod;
			secondhash = (secondhash * base2 + smt[it - 'a']) % mod2;
		}
		fout << (_hash[thishash] & _hash2[secondhash]) << '\n';
	}

}
