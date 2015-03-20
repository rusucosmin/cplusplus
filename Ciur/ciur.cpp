#include <fstream>
#include <bitset>

using namespace std;

const int maxn = 2000005;

bitset <maxn> ciur;
int n;

int main() {
	ifstream fin("ciur.in");
	ofstream fout("ciur.out");

	fin >> n;
	int ans = 0;
	for(int i = 2 ; i <= n ; ++ i) {
		if(!ciur[i]) {
			++ ans;
			for(int j = i + i ; j <= n ; j += i)
				ciur[j] = 1;
		}
	}
	fout << ans << '\n';
}
