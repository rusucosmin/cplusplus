#include <iostream>
#include <fstream>

using namespace std;

inline void gcd(int a, int b, int &x, int &y) {
	if(!b) {
		x = 1;
		y = 0;
		return ;
	}
	int x0, y0;
	gcd(b, a % b, x0, y0);
	x = y0;
	y = x0 - (a / b) * y0;
}

inline int invmod(int a, int n) {
	int x, y;
	gcd(a, n, x, y);
	x %= n;
	while(x < 0)
		x += n;
	return x;
}

int main() {
	ifstream fin("inversmodular.in");
	ofstream fout("inversmodular.out");
	int a, n;
	fin >> a >> n;
	fout << invmod(a, n) << '\n';
}
