#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const int maxn = 30005;

int n, a, b, nr, sz[maxn];

int main() {
	ifstream fin("ab2.in");
	ofstream fout("ab2.out");
	fin >> n >> a >> b;

	int remaining = n;
	for(int i = a - 1 ; i >= 0 ; -- i) {
		sz[i] = min(remaining - i, b);
		remaining -= sz[i];
	}
	for(int i = 0 ; i < a ; ++ i) {
		for(int j = remaining + sz[i] ; j > remaining ; -- j)
			fout << j << ' ';
		remaining += sz[i];
	}

}
