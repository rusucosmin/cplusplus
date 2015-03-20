#include <fstream>
#include <iostream>

using namespace std;

const int maxn = 105;

int cnt[maxn][maxn], a[maxn], b[maxn], col[maxn][maxn], st[maxn];/// cnt[i][j] = number of rocks painted j in the i-th pile
int n, k;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("509b.in", "r", stdin);
	freopen("509b.out", "w", stdout);
	#endif
	cin >> n >> k;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> a[i];
		b[i] = a[i];
	}
	for(int c = 1 ; c <= k ; ++ c) {
		int mini = 0x3f3f3f3f;
		for(int i = 1 ; i <= n ; ++ i)
			mini = min(mini, a[i]);
		for(int i = 1 ; i <= n ; ++ i) {
			a[i] -= mini;
			for(int j = 1 ; j <= mini ; ++ j)
				col[i][++st[i]] = c;
			if(a[i])
				col[i][++st[i]] = c, -- a[i];
		}
	}
	for(int i = 1 ; i <= n ; ++ i)
		if(a[i]) {
			cout << "NO\n";
			return 0;
		}
	cout << "YES\n";
	for(int i = 1 ; i <= n ; ++ i) {
		for(int j = 1 ; j <= b[i] ; ++ j)
			cout << col[i][j] << ' ';
		cout << '\n';
	}
}
