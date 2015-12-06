#include <iostream>
#include <fstream>

using namespace std;

const int maxn = 1030;

ifstream fin("cmlsc.in");
ofstream fout("cmlsc.out");

int n, m, a[maxn], b[maxn], dp[maxn][maxn];

inline void reconstr(int x, int y) {
	if(!x || !y)
		return ;
	if(a[x] == b[y]) {
		reconstr(x - 1, y - 1);
		fout << a[x] << ' ';
		return ;
	}
	if(dp[x][y - 1] > dp[x - 1][y])
		reconstr(x, y - 1);
	else
		reconstr(x - 1, y);
}

int main() {
	fin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i)
		fin >> a[i];
	for(int j = 1 ; j <= m ; ++ j)
		fin >> b[j];
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= m ; ++ j)
			if(a[i] == b[j])
				dp[i][j] = 1 + dp[i - 1][j - 1];
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
	fout << dp[n][m] << '\n';
	reconstr(n, m);
}
