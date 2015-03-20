#include <fstream>

using namespace std;

inline int extendedgcd(int a, int b, int &x, int &y) {
	if(!b) {
		x = 1;
		y = 0;
		return a;
	}
	int x0, y0;
	int gcd = extendedgcd(b, a % b, x0, y0);
	x = y0;
	y = x0 - (a / b) * y0;
	return gcd;
}

int main() {
	ifstream fin("euclid3.in");
	ofstream fout("euclid3.out");
	int n;
	fin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		int x, y, a, b, c;
		fin >> a >> b >> c;
		int gcd	= extendedgcd(a, b, x, y);
		if(c % gcd)
			fout << "0 0\n";
		else
			fout << x * (c / gcd) << ' ' << y * (c / gcd) << '\n';
	}
}
