#include <fstream>

using namespace std;

const int MAXN = 100005;

struct node {
	long long lazy, min;
	int posmin;
} arb[MAXN << 2];

int N, a[MAXN];

inline void build(int node, int st, int dr) {
	if(st == dr) {
		arb[node].lazy = 0;
		arb[node].posmin = st;
		arb[node].min = 1LL* a[st];
		return ;
	}
	int mid = ((st + dr) >> 1);
	build(node << 1, st, mid);
	build((node << 1)|1, mid + 1, dr);
	arb[node].min = min(arb[node << 1].min, arb[(node << 1)|1].min);
	if(arb[node].min == arb[node << 1].min)
		arb[node].posmin = arb[node << 1].posmin;
	else
		arb[node].posmin = arb[(node << 1)|1].posmin;
}

inline void lazyupdate(int node, int st, int dr, long long value) {
	arb[node].lazy += value;
	arb[node].min += value;
}

inline void update(int node, int st, int dr, int x, int y, long long value) {
	if(x <= st && dr <= y) {
		lazyupdate(node, st, dr, value);
		return;
	}
	int mid = ((st + dr) >> 1);
	if(arb[node].lazy) {
		lazyupdate(node << 1, st, mid, arb[node].lazy);
		lazyupdate((node << 1) | 1, mid + 1, dr, arb[node].lazy);
		arb[node].lazy = 0;
	}
	if(x <= mid)
		update(node << 1, st, mid, x, y, value);
	if(mid < y)	
		update((node << 1) | 1, mid + 1, dr, x, y, value);
	arb[node].min = min(arb[node << 1].min, arb[(node << 1)|1].min);
	if(arb[node].min == arb[node << 1].min)
		arb[node].posmin = arb[node << 1].posmin;
	else
		arb[node].posmin = arb[(node << 1)|1].posmin;
}

int main() {
	ifstream fin("biscuiti.in");
	ofstream fout("biscuiti.out");
	fin >> N;	
	long long ans = 0; 	
	for(int i = 1 ; i <= N ; ++ i) { 
		fin >> a[i];
		ans -= a[i];
	}

	build(1, 1, N);
	
	for(int i = 1 ; i <= N ; ++ i) {
		ans += arb[1].min;
	//	fout << arb[1].min << '\n';
		int aux = arb[1].posmin;
		update(1, 1, N, aux, aux, 1LL<<60);
		update(1, 1, N, 1, aux, 1LL*i);
	}
	fout << ans << '\n';
	
}
