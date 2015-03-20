#include <fstream>
#include <bitset>

using namespace std;

ifstream fin("damesah.in");
ofstream fout("damesah.out");

const int maxn = 14;

bitset <maxn> dp, ds, used;
int n, st[maxn], goodconf;

inline void back(int k) {
	if(k == n + 1) {
		if(!goodconf ++)
			for(int i = 1 ; i <= n ; ++ i)
				fout << st[i] << ' ';
		return ;
	}
	for(int i = 1 ; i <= n ; ++ i)
		if(!used[i] && !ds[k + i] && !dp[n + k - i]) {
			used[i] = ds[k + i] = dp[n + k - i] = 1;
			st[k] = i;
			back(k + 1);
			used[i] = ds[k + i] = dp[n + k - i] = 0;
		}
}

int main() {
	fin >> n;
	back(1);
	fout << '\n' <<  goodconf;
	fin.close();
	fout.close();
}
