#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int bits = 8;
const int sz = (1 << bits);
const int mask = (1 << bits) - 1;
const int times = 32 / 8;

inline void radixsort(vector <int> &v) {
	int n = v.size();
	vector <int> aux(n);
	for(int i = 0 ; i < times ; ++ i) {
		vector <int> cnt(sz, 0);
		for(auto it : v)
			++ cnt[(it >> (bits * i)) & mask];
		for(int i = 1 ; i < sz ; ++ i)
			cnt[i] += cnt[i - 1];
		for(int j = v.size() - 1 ; j >= 0 ; -- j)
			aux[--cnt[(v[j] >> (bits * i)) & mask]] = v[j];
		v = aux;
	}
}

int main() {
	ifstream fin("radixsort.in");
	ofstream fout("radixsort.out");
	int n, a, b, c;
	vector <int> v;
	fin >> n >> a >> b >> c;
	v.push_back(b);
	for(int i = 1 ; i < n ; ++ i)
		v.push_back((1LL * v.back() * a + b) % c);
	radixsort(v);
	for(int i = 0 ; i < v.size() ; i += 10)
		fout << v[i] << ' ';
}
