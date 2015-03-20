#include <fstream>
#include <algorithm>

using namespace std;

const int maxn = 200005;

int n, x[maxn], y[maxn], p;

int main() {
	ifstream fin("perfect2.in");
	ofstream fout("perfect2.out");

	fin >> p;

	fin >> n;
	for(int i = 1 ; i <= n ; ++ i)
		fin >> x[i] >> y[i];

	if(p == 1) {
		int xmin, xmax, ymin, ymax;
		xmin = xmax = x[1];
		ymin = ymax = y[1];
		for(int i = 2 ; i <= n ; ++ i) {
			xmin = min(xmin, x[i]);
			xmax = max(xmax, x[i]);
			ymin = min(ymin, y[i]);
			ymax = max(ymax, y[i]);
		}
		fout << xmin << ' ' << ymin << ' ' << xmax << ' ' << ymax << '\n';
	}
	else {
		int dx, dy;
		int ans = 0;
		for(int i = 2 ; i <= n ; ++ i) {
			dx = abs(x[1] - x[i]);
			dy = abs(y[1] - y[i]);
			ans += (__gcd(dx, dy) == 1);
		}
		fout << ans << '\n';
	}
}
