#include <fstream>

using namespace std;

ifstream fin("camion.in");
ofstream fout("camion.out");

const int maxn = 30005;

int n, m, k, c;
int x1[maxn], x2[maxn], y1[maxn], y2[maxn];

int main() {
	fin >> n >> m >> k >> c;
	for(int i = 1 ; i <= k ; ++ i)
		fin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
	for(int r = 1 ; r <= n ; ++ r) {
		int col = c;
		for(int j = k ; j >= 1 ; -- j)
			if(x1[j] <= r && r <= x2[j])
				if(col >= y1[j])
					col += y2[j] - y1[j] + 1;
		if(col > m)
			fout << 0 << '\n';
		else
			fout << col << '\n';
	}
}
