#include <iostream>
#include <bitset>

using namespace std;

const int maxn = 105;

bitset <maxn> erased;
bitset <maxn> oui, last;
int n, m, ans;

char a[maxn][maxn];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("496c.in", "r", stdin);
	freopen("496c.out", "w", stdout);
	#endif
	cin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> (a[i] + 1);
	for(int j = 1 ; j <= m ; ++ j) {
		bool okay = true;
		for(int i = 2 ; i <= n ; ++ i) {
			if(a[i - 1][j] > a[i][j]) {
				if(!oui[i])
					okay = false;
			}
		}
		if(!okay) {
			++ ans;
			continue;
		}
		for(int i = 2 ; i <= n ; ++ i) {
			if(a[i - 1][j] < a[i][j] && !oui[i])
				oui[i] = true;
		}

	}
	cout << ans << "\n";
}
