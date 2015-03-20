#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

const int maxn = 1000005;

unordered_map<int, int> cnt;
int n, a[maxn], l[maxn], aib[maxn];

inline int lsb(int x) {
	return x & (-x);
}

inline void update(int node, int value) {
	for(int i = node ; i <= n ; i += lsb(i))
		aib[i] += value;
}

inline int query(int node) {
	int sum = 0;
	for(int i = node ; i > 0 ; i -= lsb(i))
		sum += aib[i];
	return sum;
}

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void getint(int &x) {
	x = 0;
	while(!isdigit(buff[pos]))
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	while(isdigit(buff[pos])) {
		x = x * 10 + buff[pos] - '0';
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("459d.in", "r", stdin);
	freopen("459d.out", "w", stdout);
	#endif
	getint(n);
	for(int i = 1 ; i <= n ; ++ i) {
		getint(a[i]);
		l[i] = ++ cnt[a[i]];
	}
	cnt.clear();
	long long ans = 0;
	// such pairs (i,j) such that l[i] > r[j]
	for(int i = n ; i >= 1 ; -- i) {
		ans += query(l[i] - 1); /// returns the sum [1, l[i]] from the aib
		update(++ cnt[a[i]], 1);
	}
	cout << ans << '\n';
}
