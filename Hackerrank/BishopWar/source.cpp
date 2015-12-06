#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <bitset>

using namespace std;

const int maxn = 12;
int maxmask;

char s[maxn][maxn];
int n, m, ans;
int mask[maxn];
int st[maxn];

inline void back(int k, int confst, int confdr) {
	if(k == n) {
		++ ans;
		return ; 
	}
	confst = confst & mask[k];
	confdr = confdr & mask[k];
	int conf = confst | confdr;
	for(int i = 0 ; i < m ; ++ i) {
		if(!(conf & (1 << i)) && (mask[k] & (1 << i))) {
			int newconfst = (confst | (1 << i));
			int newconfdr = (confdr | (1 << i));
			st[k] = i;
			back(k + 1, (newconfst << 1) & maxmask, (newconfdr >> 1));
		}
	}
}


int main() {
	#ifdef HOME
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	cin >> n >> m;
	cin.getline(s[0], maxn);
	maxmask = (1 << m) - 1;
	for(int i = 0 ; i < n ; ++ i) {
		cin.getline(s[i], maxn);
		for(int j = 0 ; s[i][j] ; ++ j)
			if(s[i][j] == '*')
				mask[i] += (1 << j);
		mask[i] = maxmask - mask[i]; 
	}
	back(0, 0, 0);
	cout << ans << '\n';
}
