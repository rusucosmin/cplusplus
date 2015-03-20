#include <fstream>

using namespace std;

const int maxn = 100005;
const int maxlg = 22;

int n, m, rmq[maxlg][maxn], lg[maxn];

inline int query(int x, int y) {
	int l = lg[y - x + 1];
	int ans = rmq[l][x];
	if(ans > rmq[l][y - (1 << l) + 1])
		ans = rmq[l][y - (1 << l) + 1];
	return ans;
}

int main() {
	ifstream fin("rmq.in");
	ofstream fout("rmq.out");
	fin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i)
		fin >> rmq[0][i];
	for(int i = 2 ; i <= n ; ++ i)
		lg[i] = lg[i >> 1] + 1;
	for(int i = 1 ; (1 << i) <= n ; ++ i) {
		int aux = (1 << (i - 1));
		for(int j = 1 ; j + (1 << i) - 1 <= n ; ++ j) {
			rmq[i][j] = rmq[i - 1][j];
			if(rmq[i][j] > rmq[i - 1][j + aux])
				rmq[i][j] = rmq[i - 1][j + aux];
		}
	}
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		fin >> x >> y;
		fout << query(x, y) << '\n';
	}
}
