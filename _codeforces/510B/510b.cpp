#include <fstream>
#include <iostream>
#include <bitset>
#include <stdlib.h>

using namespace std;

const int maxn = 55;

int n, m, i, j;
char s[maxn][maxn];
int used[maxn][maxn];

const int dx[] = {-1, 1, 0, 0};
const int dy[] = { 0, 0,-1, 1};

inline bool inside(int x, int y) {
	return 1 <= x && x <= n && 1 <= y && y <= m;
}

inline void dfs(int x, int y, char ch, int level) {
	used[x][y] = level;
	for(int d = 0 ; d < 4 ; ++ d) {
		int newx = x + dx[d];
		int newy = y + dy[d];
		if(inside(newx, newy) && ch == s[newx][newy]) {
			if(!used[newx][newy])
				dfs(newx, newy, ch, level + 1);
			else
				if(level - used[newx][newy] + 1 >= 4) {
					cout << "Yes\n";
					exit(0);
				}
		}
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("510b.in", "r", stdin);
	#endif
	cin >> n >> m;
	for(i = 1 ; i <= n ; ++ i)
		cin >> s[i] + 1;
	for(i = 1 ; i <= n ; ++ i)
		for(j = 1 ; j <= m ; ++ j)
			if(!used[i][j])
				dfs(i, j, s[i][j], 1);
	cout << "No\n";
}

