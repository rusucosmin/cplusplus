#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int maxn = 100005;

struct interval {
	int min, cntmin, gcd;
	interval() {
		min = 0x3f3f3f3f;
		cntmin = -1;
		gcd = 1;
	}
	void create(interval lf, interval rg) {
		gcd = __gcd(lf.gcd, rg.gcd);
		if(lf.min < rg.min) {
			min = lf.min;
			cntmin = lf.cntmin;
		}
		else if(lf.min == rg.min) {
			min = lf.min;
			cntmin = lf.cntmin + rg.cntmin;
		}
		else {
			min = rg.min;
			cntmin = rg.cntmin;
		}	
	}
} arb[maxn << 2]; 

int n, m, a[maxn];

inline void update(int node, int st, int dr, int ind, int value) {
	if(st == dr) {
		arb[node].min = value;
		arb[node].gcd = value;
		arb[node].cntmin = 1;
		return ;
	}
	int mid = ((st + dr) >> 1);
	if(ind <= mid)
		update(node << 1, st, mid, ind, value);
	else
		update((node << 1) | 1, mid + 1, dr, ind, value);
	arb[node].create(arb[node << 1], arb[(node << 1) | 1]);
}

inline interval query(int node, int st, int dr, int a, int b) {
	if(a <= st && dr <= b)
		return arb[node];
	int mid = ((st + dr) >> 1);
	interval lf, rg;
	if(a <= mid)
		lf = query(node << 1, st, mid, a, b);
	if(mid < b)
		rg = query((node << 1) | 1, mid + 1, dr, a, b);
	if(lf.cntmin == -1)
		return rg;
	if(rg.cntmin == -1)
		return lf;
	interval father;
	father.create(lf, rg);
	return father;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("474f.in", "r", stdin);
	freopen("474f.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> a[i];
		update(1, 1, n, i, a[i]);
	}
	cin >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int a, b;
		cin >> a >> b;
		interval ans = query(1, 1, n, a, b);
		if(ans.min != ans.gcd) {
			cout << b - a + 1 << '\n';
			continue;
		}
		cout << b - a + 1 - ans.cntmin << '\n';
	}
}
