#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const int mod = 333019;
const int maxn = 2005;

double x[maxn], a, b, c;
int n, dp[maxn];

int main() {
	ifstream fin("iopds.in");
	ofstream fout("iopds.out");
	fin >> a >> b >> c;
	fin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		fin >> x[i];	
	}
	for(int i = 1 ; i <= n ; ++ i) {
		dp[i] = 0;	
		for(int j = 1 ; j < i ; ++ j)
			if(a * x[i] * x[i] + b * x[j] * x[j] + c * x[i] * x[j] > 0)
				dp[i] = (dp[i] + dp[j] + 1) % mod;
	}
	int ans = 0;
	for(int i = 1 ; i <= n ; ++ i)
		ans = (ans + dp[i]) % mod;
	fout << ans << '\n';
}
