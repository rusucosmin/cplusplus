#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int maxn = 100005;

int arb[maxn << 2], a[maxn], n, m;

inline void build(int node, int st, int dr) {
	if(st == dr) {
		arb[node] = a[st];
		return ;
	}
	int mid = ((st + dr) >> 1);
	build(node << 1, st, mid);
	build((node << 1) | 1, mid + 1, dr);
	arb[node] = max(arb[node << 1], arb[(node << 1) | 1]);
}

inline void update(int node, int st, int dr, int pos, int value) {
	if(st == dr) {
		arb[node] = value;
		return ;
	}
	int mid = ((st + dr) >> 1);
	if(pos <= mid)
		update(node << 1, st, mid, pos, value);
	else
		update((node << 1) | 1, mid + 1, dr, pos, value);
	arb[node] = max(arb[node << 1], arb[(node << 1) | 1]);
}

inline int query(int node, int st, int dr, int a, int b) {
	if(a <= st && dr <= b)
		return arb[node];
	int mid = ((st + dr) >> 1);
	int ret = -0x3f3f3f3f;
	if(a <= mid)
		ret = max(ret, query(node << 1, st, mid, a, b));
	if(mid < b)
		ret = max(ret, query((node << 1) | 1, mid + 1, dr, a, b));
	return ret;
}

int main() {
	ifstream fin("arbint.in");
	ofstream fout("arbint.out");

	fin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i)
		fin >> a[i];
	build(1, 1, n);
	for(int i = 1 ; i <= m ; ++ i) {
		int type, x, y;
		fin >> type >> x >> y;
		if(type == 0)
			fout << query(1, 1, n, x, y) << '\n';
		else
			update(1, 1, n, x, y);
	}
}

