#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <bitset>

using namespace std;

const int maxn = 505;

struct ride {
	int xs, ys, xf, yf, start_time, end_time;
} a[maxn];

int t, n, match[maxn], pereche[maxn];
vector <int> g[maxn];
bitset <maxn> used;

inline int convert_time(int h, int m) {
	return h * 60 + m;
}

inline int myabs(int x) {
	if(x < 0)
		return -x;
	return x;
}

inline int dist(int a, int b, int c, int d) {
	return myabs(a - c) + myabs(b - d);
}

inline bool can(ride a, ride b) {
	return a.end_time + dist(a.xf, a.yf, b.xs, b.ys) < b.start_time;
}

inline bool pairup(int node) {
	if(used[node])
		return 0;
	used[node] = 1;
	for(auto it : g[node])
		if(!pereche[it] || pairup(pereche[it])) {
			pereche[it] = node;
			match[node] = it;
			return 1;
		}
	return 0;
}

inline int maxmatching() {
	memset(match, 0, sizeof(match));
	memset(pereche, 0, sizeof(pereche));
	int ret = 0;
	for(bool change = true ; change ; ) {
		change = false;
		used.reset();
		for(int i = 1 ; i <= n ; ++ i)
			if(!match[i] && pairup(i)) {
				++ ret;
				change = true;
			}
	}
	return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("la-3126.in", "r", stdin);
	freopen("la-3126.out", "w", stdout);
	#endif
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 1 ; i <= n ; ++ i) {
			int hh, mm;
			scanf("%d:%d %d %d %d %d", &hh, &mm, &a[i].xs, &a[i].ys, &a[i].xf, &a[i].yf);
			a[i].start_time = convert_time(hh, mm);
			a[i].end_time = a[i].start_time + dist(a[i].xs, a[i].ys, a[i].xf, a[i].yf);
		}
		for(int i = 1 ; i <= n ; ++ i)
			for(int j = 1 ; j <= n ; ++ j)
				if(i != j && can(a[i], a[j]))
					g[i].push_back(j);
		cout << n - maxmatching() << '\n';
		for(int i = 1 ; i <= n ; ++ i)
			vector <int> ().swap(g[i]);
	}
}
