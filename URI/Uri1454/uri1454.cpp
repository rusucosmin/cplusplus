#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include <cassert>

using namespace std;

const int maxn = 115;
const int oo = 0x3f3f3f3f;

int rf[maxn][maxn], n, m, k, test;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uri1454.in", "r", stdin);
	freopen("uri1454.out", "w", stdout);
	#endif
	while(true) {
		memset(rf, oo, sizeof(rf));
		cin >> n >> m;	
		if(n + m == 0)
			return 0;
		for(int i = 1 ; i <= m ; ++ i) {
			int x, y, z;
			cin >> x >> y >> z;
			rf[x][y] = min(rf[x][y], z);
			rf[y][x] = min(rf[y][x], z);
		}
		for(int k = 1 ; k <= n ; ++ k)
			for(int i = 1 ; i <= n ; ++ i)
				for(int j = 1 ; j <= n ; ++ j)
					if(rf[i][j] > max(rf[i][k], rf[k][j]))
						rf[i][j] = max(rf[i][k], rf[k][j]);
		cout << "Instancia " << ++ test << '\n';
		cin >> k;
		for(int i = 1 ; i <= k ; ++ i) {
			int x, y;
			cin >> x >> y;
			assert(rf[x][y] != oo);
			if(x == y)
				cout << "0\n";
			else
				cout << rf[x][y] << '\n';
		}
		cout << '\n';
	}
	
}
