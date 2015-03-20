#include <fstream>
#include <vector>
#include <string.h>
#include <iostream>
#include <unordered_map>

using namespace std;

const int maxn = 105;

int t, n, m, q, dad[maxn][maxn], rf[maxn][maxn];
unordered_map <string, int> idx;
string s[maxn];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uri1427.in", "r", stdin);
	freopen("uri1427.out", "w", stdout);
	#endif
	cin >> t;
	while (t --) {
		idx.clear();
		memset(dad, 0, sizeof(dad));
		memset(rf, 0x3f3f3f3f, sizeof(rf));
		cin >> n;
		for(int i = 1 ; i <= n ; ++ i) {
			cin >> s[i];
			idx[s[i]] = i;
		}
		for(int k = n + 1 ; k ; -- k) {
			for(int i = 1 ; i <= n ; ++ i)
				for(int j = 1 ; j <= n ; ++ j) {
					if(k == n + 1) {
						cin >> rf[i][j];
						if(rf[i][j] <= 0)
							rf[i][j] = 0x3f3f3f3f;
						else
							dad[i][j] = j;
						continue;
					}
					if(rf[i][j] > rf[i][k] + rf[k][j] || (rf[i][j] == rf[i][k] + rf[k][j] && dad[i][j] > dad[i][k])) {
						rf[i][j] = rf[i][k] + rf[k][j];
						dad[i][j] = dad[i][k];
					}
				}
		}
		cin >> q;
		while (q -- ) {
			string a, b, c;
			cin >> a >> b >> c;
			int x = idx[b];
			int y = idx[c];
			if(rf[x][y] == 0x3f3f3f3f || dad[x][y] == 0)
				cout << "Sorry Mr " << a << " you can not go from " << b << " to " << c << "\n";
			else {
				cout << "Mr " << a << " to go from " << b << " to " << c << ", you will receive " << rf[x][y] << " euros\n";
				cout << "Path:" << b;
				while(x != y) {
					x = dad[x][y];
					cout << " " << s[x];
				}
				cout << '\n';
			}
		}
	}

}
