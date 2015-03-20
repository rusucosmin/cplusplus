#include <fstream>

using namespace std;

inline int gcd(int a, int b) {
	if(!b)
		return a;
	return gcd(b, a % b);
}

int main() {
	ifstream fin("euclid2.in");
	ofstream fout("euclid2.out");
	int t;
	fin >> t;
	while (t --) {
		int a, b;
		fin >> a >> b;
		fout << gcd(a, b) << '\n';
	}
}
