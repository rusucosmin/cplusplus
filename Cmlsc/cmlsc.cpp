#include <iostream>
#include <fstream>

using namespace std;

const int maxn = 1030;

int n, m, a[maxn], b[maxn], dp[maxn][maxn];

inline void reconstr(int i, int j, ofstream & fout) {
	if(!i || !j)
		return ;
	if(a[i] == b[j]) {
		reconstr(i - 1, j - 1, fout);
		fout << a[i] << ' ';
		return ;
	}
	if(dp[i - 1][j] > dp[i][j - 1])
		reconstr(i - 1, j, fout);
	else
		reconstr(i, j - 1, fout);
}

int main() {
	ifstream fin("cmlsc.in");
	ofstream fout("cmlsc.out");

	fin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i)
		fin >> a[i];
	for(int i = 1 ; i <= m ; ++ i)
		fin >> b[i];
	
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= m ; ++ j)
			if(a[i] == b[j])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

	fout << dp[n][m] << '\n';
	reconstr(n, m, fout);
}
