#include <fstream>
#include <algorithm>
#include <bitset>

using namespace std;

const int maxn = 100005;

int n, a[maxn], b[maxn];
bitset <maxn> used;


int main() {
	ifstream fin("perm2.in");
	ofstream fout("perm2.out");
	fin >> n;
	for(int i = 1 ; i <= n ; ++ i)
		fin >> a[i];
	for(int i = 1 ; i <= n ; ++ i) {
		if(used[a[i]])
			continue;
		int c = 1;
		int q = a[i];
		used[q] = 1;
		while(q != i) {
			q = a[q];
			used[q] = 1;
			++ c;
		}
		b[++ b[0]] = c;
	}
	int cmmmc = 0;
	for(int i = 1 ; i <= b[0] ; ++ i)
		if(b[i] != 0) {
			if(cmmmc == 0)
				cmmmc = b[i];
			else
				cmmmc = (cmmmc * b[i]) / __gcd(cmmmc, b[i]);
		}
	fout << cmmmc << '\n';
}
