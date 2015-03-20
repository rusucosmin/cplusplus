#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#include <fstream>
#include <stdio.h>

using namespace std;

const int maxn = 100005;

int t = 10, n, arb[maxn << 2], a[maxn], lis[maxn], lds[maxn];

inline void update(int node, int st, int dr, int x, int value) {
	if(st == dr) {
		arb[node] = value;
		return;
	}
	int mid = ((st + dr) >> 1);
	if(x <= mid)
		update(node << 1, st, mid, x, value);
	else
		update((node << 1) | 1, mid + 1, dr, x, value);
	arb[node] = max(arb[node << 1], arb[(node << 1) | 1]);
}

inline int query(int node, int st, int dr, int a, int b) {
	if(a <= st && dr <= b)
		return arb[node];
	int mid = ((st + dr) >> 1);
	int ans = 0;
	if(a <= mid)
		ans = max(ans, query(node << 1, st, mid, a, b));
	if(mid < b)
		ans = max(ans, query((node << 1) | 1, mid + 1, dr, a, b));
	return ans;
}

int main() {
	#ifndef ONLINE_JUDGE
		freopen("spoj-supper.in", "r", stdin);
		freopen("spoj-supper.out", "w", stdout);
	#endif
	while (t -- ) {
		cin >> n;
		memset(arb, 0, sizeof(arb));
		int maxi = 1;
		for(int i = 1 ; i <= n ; ++ i) {
			cin >> a[i];
			lis[i] = 1 + query(1, 1, n, 1, a[i]);
			update(1, 1, n, a[i], lis[i]);
			maxi = max(maxi, lis[i]);	
		}
		memset(arb, 0, sizeof(arb));
		for(int i = n ; i ; -- i) {
			lds[i] = 1 + query(1, 1, n, a[i], n);
			update(1, 1, n, a[i], lds[i]);
		}
		vector <int> ans;
		bool ok = false;
		for(int i = 1 ; i <= n ; ++ i)
			if(lis[i] + lds[i] - 1 == maxi)
				ans.push_back(a[i]);
		sort(ans.begin(), ans.end());
		cout << ans.size() << "\n";
		for(int i = 0 ; i < ans.size() ; ++ i)
			if(i != ans.size() - 1)
				cout << ans[i] << ' ';
			else
				cout << ans[i];
		if(t)
		cout << '\n';
	}
}
