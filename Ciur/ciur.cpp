#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const int maxn = 2000005;

int n, cnt;
bitset <maxn> used;

int main() {
	ifstream fin("ciur.in");
	ofstream fout("ciur.out");
	fin >> n;

	for(int i = 2 ; i <= n ; ++ i) {
		if(used[i])
			continue;
		++ cnt;
		for(int j = i + i ; j <= n ; j += i) {
			used[j] = 1;	

		}
	}
	fout << cnt << '\n';
}
