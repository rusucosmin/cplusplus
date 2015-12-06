#include <iostream>
#include <unordered_map>
#include <string.h>
#include <algorithm>

using namespace std;

const int maxn = 1000005;

int cnt[1 << 26];
int t, n;
char s[maxn];
int putere[26];

inline long long gcd(long long a, long long b) {
	if(!b)
		return a;
	return gcd(b, a % b);
}

int main() {
	#ifdef HOME
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
	#endif
	cin >> t;
	putere[0] = 1;
	for(int i = 1 ; i < 26 ; ++ i)
		putere[i] = putere[i - 1] * 2;
	while(t -- ) {
		cin >> (s + 1);
		n = strlen(s + 1);
		memset(cnt, 0, sizeof(cnt));
		++ cnt[0];
		long long q, p = 0;
		int mask = 0;
		if(n % 2 == 0)
			q = 1LL* (n / 2) * (n + 1);
		else
			q = 1LL * n * ((n + 1) / 2);
		int conf = 0;
		for(int i = 1 ; i <= n ; ++ i) {
			conf = (conf ^ putere[s[i] - 'a']);
			mask = mask | putere[s[i] - 'a'];
			p += cnt[conf];
			for(int j = 0 ; j < 26 ; ++ j)
				if(mask & putere[j])
					p += cnt[conf ^ putere[j]];
			++ cnt[conf];
		}
		long long cmmdc = gcd(p, q);
		cout << p / cmmdc << '/' << q / cmmdc << '\n';
	}
}
