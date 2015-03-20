#include <fstream>
#include <queue>
#include <bitset>

using namespace std;

const int maxn = 1005;

int n, m, l;
bitset <maxn> a[maxn], act[maxn];
int mars[maxn][maxn], sum[maxn][maxn];

int main() {
	ifstream fin("electrica.in");
	ofstream fout("electrica.out");
	
	fin >> n >> m >> l;
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= m ; ++ j) {	
			char s;
			fin >> s;
			a[i][j] = s - '0';
		}

	int ans = 0;
	
	for(int i = 1 ; i + l - 1 <= n ; ++ i)
		for(int j = 1 ; j + l - 1 <= m ; ++ j) {
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + mars[i][j];
			if(sum[i][j] % 2 == 1)
				act[i][j] = !act[i][j];
			if(act[i][j] != a[i][j]) {
				act[i][j] = !a[i][j];	
				++ ans;	
				mars[i][j] += 1;
				mars[i + l][j] -= 1;
				mars[i][j + l] -= 1;
				mars[i + l][j + l] += 1;
				sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + mars[i][j];
			}
		}
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= m ; ++ j) {
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + mars[i][j];
			act[i][j] = sum[i][j] % 2;
			if(a[i][j] != act[i][j]) {
				fout << "-1\n";
				return 0;
			}
		}

	fout << ans << '\n';
}
