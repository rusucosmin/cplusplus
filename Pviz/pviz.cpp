#include <fstream>

using namespace std;

const int maxn = 2005;
const int mod = 10007;

int dp[2][maxn], n, m, x[maxn];

int main() {
	ifstream fin("pviz.in");
	ofstream fout("pviz.out");

	fin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i)
		fin >> x[i];
	dp[1][1] = 1;
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= m ; ++ j) {
			bool act = i & 1;
			if(i == 1 && j == 1)
				continue;
			dp[act][j] = (dp[!act][j - 1] + (x[j] - i + 1) * dp[!act][j]) % mod;
		}
	fout << dp[n&1][m] << '\n';
}
