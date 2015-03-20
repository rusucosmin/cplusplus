#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int n, m;
	ifstream fin("reflex.in");
	ofstream fout("reflex.out");
	fin >> n >> m;
	-- n; -- m;
	int gcd = __gcd(n, m);
	int hs = n / gcd;
	int vs = m / gcd;
	int colt = 1;
	if(hs % 2 == 0)
		colt = 4;
	else
		if(vs % 2 == 0)
			colt = 2;
		else
			colt = 3;
	fout << (1LL * n * m) / gcd + 1 << ' ' << colt << '\n';
	fout << vs - 1 << ' ' << hs - 1 << '\n';
}
