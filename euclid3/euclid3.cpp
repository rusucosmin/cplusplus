#include <iostream>
#include <fstream>

using namespace std;

/// a * x0 + b * y0 = d
/// gcd(a, b) = gcd(b, a % b)
/// a = b * [a / b] + a % b = > a % b = a - b * [a / b];
/// a * x0 + b * y0 = d
/// b * x1 + (a - b * q) * y1 = d
///
/// a * x0 + b * y0 = b * x1 + a * y1 - b * q * y1

/// a * (x0 - y1) + b * (y0 - x1 + q * y1) = 0;

// y1 = x0
// x1 = y0 - q * y1 = y0 - q * x0
// y0 = x1 + q * y1



/// a * (x0 - y1) + b * (y0 - x1 + q * y1) = 0
/// y1 = x0
//  y0 - x1 + q * y1 = 0 => y1 = (x1 - y0) / q

int extendedGcd(int a, int b, int &x, int &y) {
	if(!b) {
		x = 1;
		y = 0;
		return a;
	}
	int x0, y0;
	int gcd = extendedGcd(b, a % b, x0, y0);
	x = y0;
	y = x0 - (a / b) * y0;
	return gcd;
}

int main() {
	ifstream fin("euclid3.in");
	ofstream fout("euclid3.out");
	
	int t;
	fin >> t;
	while(t --) {
		int a, b, c;
		fin >> a >> b >> c;
		int x, y;
		int gcd = extendedGcd(a, b, x, y);
		if(c % gcd)
			fout << "0 0\n";
		else
			fout << x * (c / gcd)  << ' ' << y * (c / gcd) << '\n';
	}
}
