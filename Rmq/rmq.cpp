#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("rmq.in");
ofstream fout("rmq.out");

const int maxn = 100005;
const int maxlg = 20;

int n, m, rmq[maxlg][maxn], lg[maxn];

int main() {
	int n, m;
	fin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i)
		fin >> rmq[0][i];
	for(int i = 2 ; i <= n ; ++ i)
		lg[i] = lg[i >> 1] + 1;
	for(int i = 1 ; (1 << i) <= n ; ++ i)
		for(int j = 1 ; j + (1 << i) - 1 <= n ; ++ j)
			rmq[i][j] = min(rmq[i - 1][j], rmq[i - 1][j + (1 << (i - 1))]);
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		fin >> x >> y;
		int l = lg[y - x + 1];
		int ret = rmq[l][x];
		ret = min(ret, rmq[l][y - (1 << l) + 1]);
		fout << ret << '\n';
	}
}
