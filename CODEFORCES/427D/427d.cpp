#include <fstream>
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

const int maxn = 5005;

string a, b;
int lcp[maxn][maxn], uniqa[maxn], uniqb[maxn];

inline void make_lcp(string a, string b, int lcp[maxn][maxn]) {
	for(int i = a.size() - 1 ; i >= 0 ; -- i)
		for(int j = b.size() - 1 ; j >= 0 ; -- j)
			if(a[i] == b[j])
				lcp[i][j] = 1 + lcp[i + 1][j + 1];
			else
				lcp[i][j] = 0;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("427d.in", "r", stdin);
	freopen("427d.out", "w", stdout);
	#endif
	cin >> a >> b;
	make_lcp(a, a, lcp);
	for(int i = 0 ; i < a.size() ; ++ i) {
		int act = 0;
		for(int j = 0 ; j < a.size() ; ++ j) {
			if(i == j)
				continue;
			act = max(act, lcp[i][j]);
		}
		++ act;
		uniqa[i] = act;
	}
	memset(lcp, 0, sizeof(lcp));
	make_lcp(b, b, lcp);
	for(int i = 0 ; i < b.size() ; ++ i) {
		int act = 0;
		for(int j = 0 ; j < b.size() ; ++ j) {
			if(i == j)
				continue;
			act = max(act, lcp[i][j]);
		}
		++ act;
		uniqb[i] = act;
	}
	memset(lcp, 0, sizeof(lcp));
	make_lcp(a, b, lcp);
	int ans = 0x3f3f3f3f;
	for(int i = 0 ; i < a.size() ; ++ i)
		for(int j = 0 ; j < b.size() ; ++ j)
			if(lcp[i][j] >= max(uniqa[i], uniqb[j]))
				ans = min(ans, max(uniqa[i], uniqb[j]));
	if(ans == 0x3f3f3f3f)
		ans = -1;
	cout << ans << '\n';
}
