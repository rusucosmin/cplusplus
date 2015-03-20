#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;

int r, xa, ya, xb, yb;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("507b.in", "r", stdin);
	freopen("507b.out", "w", stdout);
	#endif

	cin >> r >> xa >> ya >> xb >> yb;

	if(xa == xb && ya == yb) {
		cout << "0\n";
		return 0;
	}


	double distance = sqrt((xa - xb) * (xa - xb) + (ya - yb) * (ya - yb));

	double ans = (distance / (2 * r)) + (((int)(distance / (2 * r)) * (r * 2) == 0));

	
	cout << floor(ans) + ((ans - floor(ans)) != 0) << '\n';
}
