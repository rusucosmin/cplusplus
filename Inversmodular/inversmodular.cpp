#include <fstream>
#include <iostream>

using namespace std;

int a, n;

void gcd(int a, int n, int &x, int &y) {
	if(!n) {
		/// a * x + b * y = cmmdc(a, b) = a;	
		x = 1;
		y = 0;
		return ;
	}
	int x0, y0;
	gcd(n, a % n, x0, y0);
	/// b * x0 + (a % b) * y0 = cmmdc(a, b) = 
	/// a * x + b * y = cmmdc(a, b)
	/// b * x0 + a = (a/b) * b + a % b =>
	x = y0;
	y = x0 - (a / n) * y0;
}

int main() {
	freopen("inversmodular.in", "r", stdin);
	freopen("inversmodular.out", "w", stdout);
	cin >> a >> n;
	int x, y;
	gcd(a, n, x, y);
	while(x < 0)
		x += n;
	cout << x << '\n';
}
