#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

const int maxn = 1000005;

char s[maxn];
int z[maxn], n;

inline int expand(int x, int y) {
	int ret = 0;
	for(int i = x, j = y ; j < n ; ++ i, ++ j) {
		if(s[i] != s[j])
			return ret;
		++ ret;
	}
	return ret;
}

inline void buildz() {
	z[0] = 0;
	int l = -1, r = -1;
	for(int i = 1 ; i < n ; ++ i) {
		if(i > r) {
			z[i] = expand(0, i);
			if(z[i] != 0) {
				l = i;
				r = i + z[i] - 1;
			}
		}
		else {
			int k = i - l, b = r - i + 1;
			if(z[k] < b) {
				z[i] = z[k];
				continue;
			}
			z[i] = b + expand(b, r + 1);
			if(i + z[i] - 1 > r) {
				r = i + z[i] - 1;
				l = i;
			}
		}
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("126b.in", "r", stdin);
	freopen("126b.out", "w", stdout);
	#endif

	cin.getline(s, maxn);
	n = strlen(s);
	buildz();

	int maxsofar = 0;
	int ans = 0;
	for(int i = 1 ; i < n ; ++ i) {
		if(i + z[i] - 1 == n - 1 && z[i] <= maxsofar)
			ans = max(ans, z[i]);
		maxsofar = max(maxsofar, z[i]);
	}
	if(ans == 0) {
		cout << "Just a legend\n";
		return 0;
	}
	for(int i = 0 ; i < ans ; ++ i)
		cout << s[i];
	return 0;
}
