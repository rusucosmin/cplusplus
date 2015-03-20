#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int maxg = 10005;
const int maxn = 5005;

int n, g, dp[2][maxg], w[maxn], p[maxn];

int main() {
	ifstream fin("rucsac.in");
	ofstream fout("rucsac.out");

	fin >> n >> g;
	for(int i = 1 ; i <= n ; ++ i)
		fin >> w[i] >> p[i];
	/// dp[i][j] = profitul maxim pe care il pot obtine dintr-o submultime din (1, i) cu suma greutatilor j
	/// dp[i][j] = max(dp[i - 1][j - w[i]] + p[i], dp[i - 1][j]);
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= g ; ++ j) {
			dp[i & 1][j] = dp[(i & 1) ^ 1][j];
			if(j >= w[i])
				dp[i & 1][j] = max(dp[i & 1][j], dp[(i & 1) ^ 1][j - w[i]] + p[i]);
		}
	int ans = 0;
	for(int j = 0 ; j <= g ; ++ j)
		ans = max(ans, dp[n & 1][j]);
	fout << ans << '\n';
}
