#include <iostream>
#include <fstream>
#include <algorithm>
#include <cassert>

using namespace std;

const int maxn = 60;

string b, a;
int n, pi[maxn];

long long pow2[maxn];

inline string getRepr(int act) {
	string ret = "";
	while(act) {
		ret.push_back(char(act % 2 + '0'));
		act /= 2;
	}
	reverse(ret.begin(), ret.end());
	return ret;
}

int main() {
	ifstream fin("infinitepatternmatching.in");
	ofstream fout("infinitepatternmatching.out");

	fin >> b;
	n = b.size();

	b = " " + b;

	pi[1] = 0;
	int k = 0;
	for(int i = 2 ; i < b.size() ; ++ i) {
		while(k > 0 && b[k + 1] != b[i])
			k = pi[k];
		if(b[k + 1] == b[i])
			++ k;
		pi[i] = k;
	}
	int act = 0;
	k = 0;
	int poz = 0;
	while(true) {
		++ act;
		string repr = getRepr(act);
		for(int i = 0 ; i < repr.size() ; ++ i) {
			++ poz;
			while(k > 0 && b[k + 1] != repr[i]) {
				k = pi[k];
			}
			if(b[k + 1] == repr[i])
				++ k;
			if(k == n) {
				fout << poz << '\n';
				return 0;
			}
		}
	}
	assert(false);
	return 0;
}
