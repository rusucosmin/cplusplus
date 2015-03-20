#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>

using namespace std;

const int maxn = 505;
const int maxm = 1005;

int n, m, w[maxn], d[maxm], st[maxn];
bitset <maxn> used;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("500c.in", "r", stdin);
	freopen("500c.out", "w", stdout);
	#endif
	cin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> w[i];
	for(int i = 1 ; i <= m ; ++ i) {
		cin >> d[i];
		if(!used[d[i]]) {
			st[ ++ st[0] ] = d[i];
			used[d[i]] = 1;
		}
	}
	for(int i = 1 ; i <= n ; ++ i) {
		if(!used[i])
			st[++ st[0]] = i;
	}
	int ans = 0;
	for(int i = 1 ; i <= m ; ++ i) {
		for(int j = 1 ; j <= n ; ++ j) {
			if(st[j] == d[i]) {
				for(int k = j ; k > 1 ; -- k)
					st[k] = st[k - 1];
				st[1] = d[i];
				break;
			}
			ans += w[st[j]];
		}
	}
	cout << ans << '\n';
}


