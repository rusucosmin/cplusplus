#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

const double eps = 0.000000001;
const int maxn = 1005;

int n, l, a[maxn];

inline bool check(double d) {
	if(a[1] - d > 0)
		return false;
	if(a[n] + d < l)
		return false;
	for(int i = 1 ; i < n ; ++ i)
		if(a[i] + d < a[i + 1] - d)
			return false;	
	return true;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("492b.in", "r", stdin);
	freopen("492b.out", "w", stdout);
	#endif

	cin >> n >> l;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> a[i];
	sort(a + 1, a + n + 1);

	double li = 0, ls = l, ans = l;
	while(ls - li >= eps) {
		double mid = ((li + ls) / 2);
		//cerr << mid << ' ';
		if(check(mid)) {
			ls = mid;
			ans = mid;
		}
		else {
			li = mid;	
		}
	}
	cout << fixed << setprecision(9) << ans << '\n';
}
