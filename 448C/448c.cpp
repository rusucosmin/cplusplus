#include <fstream>
#include <iostream>

using namespace std;

const int maxn = 5005;
const int maxlg = 21;

int rmq[maxlg][maxn], a[maxn], n, lg[maxn];

inline int query(int st, int dr) {
	int l = lg[dr - st + 1];
	int ans = rmq[l][st];
	if(a[ans] > a[rmq[l][dr - (1 << l) + 1]])
		ans = rmq[l][dr - (1 << l) + 1];
	return ans;
}

inline long long dei(int st, int dr, int h) {
	if(st > dr)
		return 0;
	int minpos = query(st, dr);
	return min((long long)(dr - st + 1), dei(st, minpos - 1, a[minpos]) + dei(minpos + 1, dr,a[minpos]) + a[minpos] - h);
}

int main() {
	cin.sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	freopen("448c.in", "r", stdin);
	freopen("448c.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> a[i];
		rmq[0][i] = i;
	}
	for(int i = 2 ; i <= n ; ++ i)
		lg[i] = lg[i >> 1] + 1;
	for(int i = 1 ; (1 << i) <= n ; ++ i)
		for(int j = 1 ; j + (1 << i) - 1 <= n ; ++ j) {
			rmq[i][j] = rmq[i - 1][j];
			if(a[rmq[i][j]] > a[rmq[i - 1][j + (1 << (i - 1))]])
				rmq[i][j] = rmq[i - 1][j + (1 << (i - 1))];
		}
	cout << dei(1, n, 0) << '\n';
}
