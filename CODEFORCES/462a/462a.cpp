#include <iostream>

using namespace std;

const int maxn = 105;
const int dx[] = {1,-1,0,0};
const int dy[] = {0,0,1,-1};

char s[maxn][maxn];
int n;

inline bool inside(int x, int y) {
	return 1 <= x && x <= n && 1 <= y && y <= n;
}

inline int check(int x, int y) {
	int ans = 0;
	for(int d = 0 ; d < 4 ; ++ d) {
		int newx = x + dx[d];
		int newy = y + dy[d];
		if(inside(newx, newy) && s[newx][newy] == 'o')
			++ ans;
	}
	return ans;
}

inline bool getanswer() {
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= n ; ++ j)
			if(check(i, j) % 2)
				return false;
	return true;
}

int main() {
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> s[i] + 1;
	if(getanswer())
		cout << "YES\n";
	else
		cout << "NO\n";
}
