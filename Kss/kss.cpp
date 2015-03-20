#include <fstream>
#include <string.h>
#include <iostream>
#include <string>

using namespace std;

typedef unsigned long long ll;

const int maxn = 1005;
const int sigma = 26;

int t, n, nxt[sigma][maxn];
char s[maxn];
ll k, dp[maxn];

inline void add(ll &x, ll y) {
	ll aux = x;
	x += y;
	if(x < aux)
		x = (1LL << 63);
}

inline void solve() {
	for(int j = 0 ; j < sigma ; ++ j)
		nxt[j][n + 1] = 0;
	for(int i = n ; i > 0 ; -- i) {
		nxt[ s[i] - 'a' ][i] = i;
		for(int j = 0 ; j < s[i] - 'a' ; ++ j)
			nxt[j][i] = nxt[j][i + 1];
		for(int j = s[i] - 'a' + 1 ; j < sigma ; ++ j)
			nxt[j][i] = nxt[j][i + 1];
	}
	ll sum = 0;
	for(int i = n ; i > 0 ; -- i) {
		dp[i] = 1;
		add(dp[i], sum);
		sum -= dp[nxt[ s[i] - 'a' ][i + 1]];
		add(sum, dp[i]);
	}
	string str = "";
	int p, e = 0, q = 1;
	for(; q <= n ;) {
		p = nxt[e][q];
		while(k > dp[p]) {
			k -= dp[p];
			++ e;
			if(e == sigma) {
				printf("-1\n");
				return ;
			}
			p = nxt[e][q];
		}
		str += (char)(e + 'a');
		e = 0;
		-- k;
		if(!k) {
			printf("%s\n", str.c_str());
			return;
		}
		q = p + 1;
	}
	printf("-1\n");
}

int main() {
	freopen("kss.in", "r", stdin);
	freopen("kss.out", "w", stdout);
	scanf("%d", &t);
	while(t --) {
		scanf("%d %llu", &n, &k);
		scanf("%s", s + 1);
		solve();
	}
}
