#include <fstream>
#include <iostream>

using namespace std;

const int maxn = 100005;

int n, m, a[maxn], where[maxn * 10];
int sum;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("474b.in", "r", stdin);
	freopen("474b.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> a[i];
		for(int j = 1 ; j <= a[i] ; ++ j)
			where[sum + j] = i;
		sum += a[i];
	}
	cin >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x;
		cin >> x;
		cout << where[x] << '\n';
	}
	
}
