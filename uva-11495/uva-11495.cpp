#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>

using namespace std;

const int maxn = 100005;

int n, aib[maxn];

inline int lsb(int x) {
	return x & (-x);
}

inline void insert(int pos, int value) {
	for(int i = pos ; i <= n ; i += lsb(i))
		aib[i] += value;
}

inline int query(int node) {
	int sum = 0;
	for(int i = node ; i > 0 ; i -= lsb(i))
		sum += aib[i];
	return sum;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("uva-11495.in", "r", stdin);
	freopen("uva-11495.out", "w", stdout);
	#endif
	while(cin >> n) {
		if(!n)
			return 0;
		memset(aib, 0, sizeof(aib));
		int ans = 0;
		for(int i = 1 ; i <= n ; ++ i) {
			int x;
			cin >> x;
			ans += i - 1 - query(x);
			insert(x, 1);
		}
		if(ans % 2 == 0)
			cout << "Carlos\n";
		else
			cout << "Marcelo\n";
	}
	
}
