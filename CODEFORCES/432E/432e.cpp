#include <fstream>
#include <iostream>

using namespace std;

const int maxn = 105;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1,  0,-1};

char a[maxn][maxn];
int n, m;

inline char getch(int x, int y, char ch) {
	bool okay = true;
	for(int d = 0 ; d < 4 && okay ; ++ d) {
		int newx = x + dx[d];
		int newy = y + dy[d];
		if(newx >= 1 && newx <= n && newx >= 1 && newy <= m && a[newx][newy] == ch)
			okay = false;
	}
	return okay;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("432e.in", "r", stdin);
	freopen("432e.out", "w", stdout);
	#endif
	cin >> n >> m;
	if(n > m)
		swap(n, m);
		for(int i = 1 ; i <= n ; ++ i) {
			for(int j = 1 ; j <= m ; ++ j) {
				char ch = 'A';
				for(ch = 'A' ; ch <= 'Z' ; ++ ch)
					if(!getch(i, j, ch))
						continue;
					else
						break;
				if(a[i][j])
					continue;
				int length = min(n - i + 1, m - j + 1);
				for(int x = i ; x <= i + length - 1 ; ++ x)
					for(int y = j ; y <= j + length - 1 ; ++ y)
						a[x][y] = ch;
			}
		}
	for(int j = 1 ; j <= m ; ++ j, cout << '\n')
		for(int i = 1 ; i <= n ; ++ i)
			cout << a[i][j];
			
}
