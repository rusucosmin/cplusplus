#include <fstream>
#include <cassert>

using namespace std;

const int maxn = 100005;

int n, m, k, p, arb[maxn << 2], a[maxn];

inline void update(int node, int st, int dr, int x, int value) {
	if( st == dr ) {
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

inline int query(int node, int st, int dr, int x, int y) {
	if(x<= st && dr <= y)
		return arb[node];
	int mid = (( st + dr ) >> 1);
	int ret = 0;
	if(x <= mid)
		ret = max(ret, query(node << 1, st, mid, x, y));
	if(mid < y)
		ret = max(ret, query((node << 1) | 1, mid + 1, dr, x, y));
	return ret;
}

int main() {
	ifstream fin("cerc5.in");
	ofstream fout("cerc5.out");
	
	fin >> p >> n >> k;
	for(int i = 1 ; i <= n ; ++ i) {
		fin >> a[i];
		int aux = 1 + query(1, 1, n, 1, a[i]);
		update(1, 1, n, a[i], aux);
		m = max(m, aux);
	}
	if(p == 1) {
		fout << m << '\n';
	}
	else
		assert(false);
}
