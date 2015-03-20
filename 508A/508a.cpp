#include <fstream>
#include <iostream>

using namespace std;

const int maxn = 1005;

bool a[maxn][maxn];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("508a.in", "r", stdin);
	freopen("508a.out", "w", stdout);
	#endif

	int n, m, k;
	cin >> n >> m >> k;
	for(int p = 1 ; p <= k ; ++ p) {
		int x, y;
		cin >> x >> y;
		a[x][y] = 1;
		if(x + 1 <= n && y + 1 <= m && a[x + 1][y] == 1 && a[x][y + 1] == 1 && a[x + 1][y + 1] == 1) {
			cout << p << '\n';
			return 0;
		}
		if(x + 1 <= n && y - 1 >= 1 && a[x + 1][y] == 1 && a[x + 1][y - 1] == 1 && a[x][y - 1] == 1) {
			cout << p << '\n';
			return 0;
		}
		if(x - 1 >= 1 && y - 1 >= 1 && a[x - 1][y] == 1 && a[x][y - 1] == 1 && a[x - 1][y - 1] == 1) {
			cout << p << '\n';
			return 0;
		}
		if(x - 1 >= 1 && y + 1 <= m && a[x - 1][y] == 1 && a[x][y + 1] == 1 && a[x - 1][y + 1] == 1) {
			cout << p << '\n';
			return 0;
		}
	}
	cout << 0 << '\n';
}
