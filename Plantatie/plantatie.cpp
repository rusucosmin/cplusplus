#include <iostream>
#include <fstream>

using namespace std;

const int maxn = 505;
const int maxlg = 15;

int rmq[maxlg][maxn][maxn], n, m, lg[maxn];

inline int query(int a, int b, int c, int d, int k) {
	int l = lg[k];
	int aux = (1 << l) - 1;
	return max(rmq[l][a][b],
			max(rmq[l][c - aux][b], 
			max(rmq[l][a][d - aux],
			rmq[l][c - aux][d - aux])));
}

int main() {
	ifstream fin("plantatie.in");
	ofstream fout("plantatie.out");

	fin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= n ; ++ j)
			fin >> rmq[0][i][j];
	for(int i = 2 ; i <= n ; ++ i)
		lg[i] = lg[i >> 1] + 1;
	for(int l = 1 ; (1 << l) <= n ; ++ l) {
		int aux = (1 << (l - 1));
		for(int i = 1 ; i <= n ; ++ i)
			for(int j = 1 ; j <= n ; ++ j)
				rmq[l][i][j] = max(rmq[l - 1][i][j], 
								max(rmq[l - 1][i + aux][j],
								max(rmq[l - 1][i][j + aux],
									rmq[l - 1][i + aux][j + aux])));
	}
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y, z;
		fin >> x >> y >> z;
		fout << query(x, y, x + z - 1, y + z - 1, z) << '\n';
	}
}
