#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>

using namespace std;

const int maxn = 1000005;
const int oo = 0x3f3f3f3f;

struct arbnode {
	int cnt, pozmax;
} arb[maxn << 2];

int a[maxn], n, m;

inline void build(int node, int st, int dr) {
	if(st == dr) {
		arb[node].cnt = 1;
		arb[node].pozmax = st;
		return ;
	}
	int mid = ((st + dr) >> 1);
	build(node << 1, st, mid);
	build((node << 1) | 1, mid + 1, dr);
	arb[node].cnt = arb[node << 1].cnt + arb[(node << 1) | 1].cnt;
	if(a[arb[node << 1].pozmax] >= a[arb[(node << 1) | 1].pozmax])
		arb[node].pozmax = arb[node << 1].pozmax;
	else
		arb[node].pozmax = arb[(node << 1) | 1].pozmax;
}

inline int querypos(int node, int st, int dr, int k) {
	if(st == dr)
		return st;
	int mid = ((st + dr) >> 1);
	if(arb[node << 1].cnt >= k)
		return querypos(node << 1, st, mid, k);
	else
		return querypos((node << 1) | 1, mid + 1, dr, k - arb[node << 1].cnt);
}

inline int query(int node, int st, int dr, int x, int y) {
	if(x <= st && dr <= y)
		return arb[node].pozmax;
	int mid = ((st + dr) >> 1);
	int first = 0, second = 0;
	if(x <= mid)
		first = query(node << 1, st, mid, x, y);
	if(mid < y)
		second = query((node << 1) | 1, mid + 1, dr, x, y);
	if(a[first] >= a[second])
		return first;
	else
		return second;
}

inline void update(int node, int st, int dr, int pos) {
	if(st == dr) {
		arb[node].cnt = 0;
		arb[node].pozmax = 0;
		return ;
	}
	int mid = ((st + dr) >> 1);
	if(pos <= mid)
		update(node << 1, st, mid, pos);
	else
		update((node << 1) | 1, mid + 1, dr, pos);
	arb[node].cnt = arb[node << 1].cnt + arb[(node << 1) | 1].cnt;
	if(a[arb[node << 1].pozmax] >= a[arb[(node << 1) | 1].pozmax])
		arb[node].pozmax = arb[node << 1].pozmax;
	else
		arb[node].pozmax = arb[(node << 1) | 1].pozmax;
}

ofstream fout("eliminare.out");

inline void traverse(int node, int st, int dr) {
	if(st == dr) {
		if(arb[node].cnt)
			fout << a[st] << '\n';
		return ;
	}
	int mid = ((st + dr) >> 1);
	traverse(node << 1, st, mid);
	traverse((node << 1) | 1, mid + 1, dr);
}

int main() {
	ifstream fin("eliminare.in");
	fin >> n >> m;
	a[0] = -oo;
	for(int i = 1 ; i <= n ; ++ i)
		fin >> a[i];
	build(1, 1, n);
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y;
		fin >> x >> y;
		int xx = querypos(1, 1, n, x);
		int yy = querypos(1, 1, n, y);
		int maxpos = query(1, 1, n, xx, yy);	
		update(1, 1, n, maxpos);
	}
	traverse(1, 1, n);
}
