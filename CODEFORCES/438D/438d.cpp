#include <fstream>
#include <iostream>

using namespace std;

const int maxn = 100005;

struct node {
	long long sum;
	int maxi;
} arb[maxn << 2];

int n, m, a[maxn];

inline void update(int node, int st, int dr, int pos, int value) {
	if(st == dr) {
		arb[node].sum = value;
		arb[node].maxi = value;
		return;
	}
	int mid = ((st + dr) >> 1);
	if(pos <= mid)
		update(node << 1, st, mid, pos, value);
	else
		update((node << 1) | 1, mid + 1, dr, pos, value);
	arb[node].sum = arb[(node << 1)].sum + arb[(node << 1) | 1].sum;
	arb[node].maxi = max(arb[node << 1].maxi, arb[(node << 1) | 1].maxi);
}

inline void modulate(int node, int st, int dr, int a, int b, int x) {
	if(st == dr) {
		arb[node].sum %= x;
		arb[node].maxi = arb[node].sum;
		return ;
	}
	int mid = ((st + dr) >> 1);
	if(a <= mid && arb[node << 1].maxi >= x)
		modulate(node << 1, st, mid, a, b, x);
	if(mid < b && arb[(node << 1) | 1].maxi >= x)
		modulate((node << 1) | 1, mid + 1, dr, a, b, x);
	arb[node].sum = (arb[node << 1].sum + arb[(node << 1) | 1].sum);
	arb[node].maxi = max(arb[node << 1].maxi, arb[(node << 1) | 1].maxi);
}

inline long long query(int node, int st, int dr, int a, int b) {
	if(a <= st && dr <= b)
		return arb[node].sum;
	int mid = ((st + dr) >> 1);
	long long ans = 0;
	if(a <= mid)
		ans += query(node << 1, st, mid, a, b);
	if(mid < b)
		ans += query((node << 1) | 1, mid + 1, dr, a, b);
	return ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("438d.in", "r", stdin);
	freopen("438d.out", "w", stdout);
	#endif
	cin.sync_with_stdio(false);
	cin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> a[i];
		update(1, 1, n, i, a[i]);
	}
	for(int i = 1 ; i <= m ; ++ i) {
		int op, x, y, mod, k;
		cin >> op;
		if(op == 1) {
			cin >> x >> y;
			cout << query(1, 1, n, x, y) << "\n";
		}
		if(op == 2) {
			cin >> x >> y >> mod;
			modulate(1, 1, n, x, y, mod);
		}
		if(op == 3) {
			cin >> k >> x;
			update(1, 1, n, k, x);
		}
	}
}
