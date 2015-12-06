#include <iostream>
#include <fstream>

using namespace std;

int gcd(int a, int b) {
	if(b == 0)
		return a;
	return gcd(b, a % b);
}

int gcdNonRecursive(int a, int b) {
	int r = 0;
	while(a % b != 0) {
		r = a % b;	
		a = b;
		b = r;
	}
	return b;
}

int main() {
	ifstream fin("euclid2.in");
	ofstream fout("euclid2.out");
	int t;
	fin >> t;
	while(t --) {
		int a, b;
		fin >> a >> b;
		fout << gcd(a, b) << '\n';
	}
}
