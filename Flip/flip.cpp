#include <fstream>
#include <iostream>

using namespace std;

const int maxn = 20;

int n, m, a[maxn][maxn], b[maxn][maxn];

int main() {
	ifstream fin("flip.in");
	ofstream fout("flip.out");

	fin >> n >> m;
	int ans = 0;
	for(int i = 0 ; i < n ; ++ i)
		for(int j = 0 ; j < m ; ++ j) {
			fin >> a[i][j];
			ans += a[i][j];
		}
	for(int conf = 0 ; conf < (1 << m) ; ++ conf) {
		int actsum = 0;
		for(int i = 0 ; i < n ; ++ i) {
			int sum = 0;	
			for(int j = 0 ; j < m ; ++ j)
				if(conf & (1 << j)) {
					b[i][j] = -a[i][j];
					sum += b[i][j];
				}
				else
					sum += a[i][j];
				
			actsum += max(sum, -sum);
		}
		ans = max(ans, actsum);	
	}
	fout << ans << '\n';
	

}

