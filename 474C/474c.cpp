#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long maxn = 105;

long long n, x[4], y[4], a[4], b[4], ans;

inline void rotate(long long &x, long long &y, long long a, long long b) {
	// this function rotates the polong long x, y 90 degrees counter-clockwise by a, b	
	x -= a;
	y -= b;
	long long newx = -y;
	long long newy = x;
	x = newx + a;
	y = newy + b;
}

inline bool check() {
	long long d[10];
	long long cnt = 0;
	for(long long i = 0 ; i < 4 ; ++ i)
		for(long long j = i + 1 ; j < 4 ; ++ j) {
			d[++ cnt] = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
			if(d[cnt] == 0)
				return false;
		}
	sort(d + 1, d + cnt + 1);
	for(long long i = 1 ; i < 4 ; ++ i)
		if(d[i] != d[i + 1])
			return false;
	if(2 * d[4] != d[5])
		return false;
	return d[5] == d[6];
}

inline void back(long long k, long long rotates) {
	if(k == 4) {
		if(check())
			ans = min(ans, rotates);
		return ;
	}
	back(k + 1, rotates);
	long long xaux = x[k];
	long long yaux = y[k];
	for(long long i = 1 ; i < 4 ; ++ i) {
		rotate(x[k], y[k], a[k], b[k]);
		back(k + 1, rotates + i);
	}
	x[k] = xaux;
	y[k] = yaux;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("474c.in", "r", stdin);
	freopen("474c.out", "w", stdout);
	#endif
	cin >> n;
	for(long long i = 1 ; i <= n ; ++ i) {
		for(long long j = 0 ; j < 4 ; ++ j)
			cin >> x[j] >> y[j] >> a[j] >> b[j];
		ans = 0x3f3f3f3f;
		back(0, 0);
		if(ans == 0x3f3f3f3f)
			cout << "-1\n";
		else
			cout << ans << '\n';
	}
	
}
