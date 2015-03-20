#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

const int maxn = 105;

int n, m;
bool a[maxn][maxn], b[maxn][maxn];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("486b.in", "r", stdin);
	freopen("486b.out", "w", stdout);
	#endif
	cin >> n >> m;
	memset(a, 1, sizeof(a));

	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= m ; ++ j) {
			cin >> b[i][j];
			if(b[i][j] == 0) {
				for(int x = 1 ; x <= m ; ++ x)
					a[i][x] = 0;
				for(int y = 1 ; y <= n ; ++ y)
					a[y][j] = 0;
			}
		}

	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= m ; ++ j)
			cin >> a[i][j];

	for(int i = 1 ; i <= n ; ++ i) {
		for(int j = 1 ; j <= m ; ++ j) {
			bool aux = 0;
			for(int x = 1 ; x <= m ; ++ x)
				aux |= a[i][x];
			for(int y = 1 ; y <= n ; ++ y)
				aux |= a[y][j];
			if(aux != b[i][j]) {
				cout << "NO\n";
				return 0;
			}
		}
	}
	cout << "YES\n";
	for(int i = 1 ; i <= n ; ++ i, cout << '\n')
		for(int j = 1 ; j <= m ; ++ j)	
			cout << a[i][j] << ' ';
}
