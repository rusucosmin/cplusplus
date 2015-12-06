#include <fstream>
#include <bitset>

using namespace std;

ifstream fin("permutari.in");
ofstream fout("permutari.out");

const int maxn = 105;

int n, st[maxn];
bitset <maxn> used;

inline void back(int k) {
	if(k == n + 1) {
		for(int i = 1 ; i <= n ; ++ i)
			fout << st[i] << ' ';
		fout << '\n';
		return ;
	}
	for(int i = 1 ; i <= n ; ++ i)
		if(!used[i]) {
			used[i] = 1;
			st[k] = i;
			back(k + 1);
			used[i] = 0;
		}
}

int main() {
	fin >> n;
	back(1);
}
