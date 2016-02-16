#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>
#include <math.h>

using namespace std;

const long double _PI = 3.14159265358979323846;

inline long double getdist(pair<long double, long double> x, pair<long double, long double> y) {
	return (long double) (x.first - y.first) * (x.first - y.first) + (long double) (x.second - y.second) * (x.second - y.second);
}

inline long double getdist(pair<long double, long double> p, pair<long double, long double> x, pair<long double, long double> y) {
	return getdist(p, make_pair((x.first + y.first) / 2.0, (x.second + y.second) / 2.0));
}


int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
	#endif
	int n;
	pair<long double, long double> p;
	cin >> n >> p.first >> p.second;
	long double rmin = 1LL * INT_MAX * INT_MAX;
	long double rmax = 0;
	vector <pair<long double, long double> > polig;
	for(int i = 0 ; i < n ; ++ i) {
		pair<long double, long double> X;
		cin >> X.first >> X.second;
		polig.push_back(X);
		rmin = min(rmin, getdist(p, X));
		rmax = max(rmax, getdist(p, X));
		if(i) {
			rmin = min(rmin, getdist(p, polig[i], polig[i - 1]));
		}
	}
	rmin = min(rmin, getdist(p, polig[0], polig[n - 1]));
	cout << fixed << setprecision(12) << _PI * (rmax - rmin) << '\n';
}
