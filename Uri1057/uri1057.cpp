#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include <cassert>

using namespace std;

const int maxn = 12;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = { 0,-1, 0, 1};

int t, n, m;
char a[maxn][maxn];
int x[3], y[3], cnt;
int lastx[3], lasty[3];
int ans;

inline bool inside(int xx, int yy) {
	return xx >= 0 && xx < n && yy >= 0 && yy < n;
}

int ret;

inline void back(int k) {
	cout << k << '\n';
	for(int i = 0 ; i < n ; ++ i)
		cout << a[i] << '\n';
	
	++ ret;
	if(ret >= 10000)
		return;
	bool ok = true;
	for(int i = 0 ; i < cnt ; ++ i)
		if(a[x[i]][y[i]] != 'X')
			ok = false;
	for(int i = 0 ; i < 4 ; ++ i) {
		bool change = false;
		for(int j = 0 ; j < 3 ; ++ j) {
			lastx[j] = x[j];
			lasty[j] = y[j];
			if(inside(x[j] + dx[i], y[j] + dy[i]))
				if((a[x[j] + dx[i]][y[j] + dy[i]] == '.' || a[x[j] + dx[i]][y[j] + dy[i]] == 'X') && a[x[j]][y[j]] != 'X') {
					change = true;
					x[j] += dx[i];
					y[j] += dy[i];
				}
			swap(a[x[j]][y[j]], a[lastx[j]][lasty[j]]);
		}
		if(change)
			back(k + 1);
		for(int j = 0 ; j < 3 ; ++ j) {
			x[j] = lastx[j];
			y[j] = lasty[j];
			swap(a[x[j]][y[j]], a[lastx[j]][lasty[j]]);
		}
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uri1057.in", "r", stdin);
	freopen("uri1057.out", "w", stdout);
	#endif
	cin >> t;
	while (t --) {
		cnt = 0;
		ans = 0x3f3f3f3f;
		cin >> n;
		for(int i = 0 ; i < n ; ++ i)
			cin >> a[i];
		for(int i = 0 ; i < n ; ++ i)
			for(int j = 0 ; j < n ; ++ j)
				if(isalpha(a[i][j]) && a[i][j] != 'X') {
					x[cnt] = i;
					y[cnt++] = j;
				}
		cout << cnt << '\n';
		assert(cnt == 3);
		back(0);
	}
}
