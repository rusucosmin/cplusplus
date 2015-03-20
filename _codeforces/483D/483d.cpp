#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 100005;

int aib[32][maxn], n, m, a[maxn];

inline int lsb(int x) {
	return x & (-x);
}

inline void update(int bit, int pos, int value) {
	for(int i = pos ; i <= n + 1 ; i += lsb(i))
		aib[bit][i] += value;
}

inline int query(int bit, int pos) {
	int sum = 0;
	for(int i = pos ; i > 0 ; i -= lsb(i))
		sum += aib[bit][i];
	return sum;
}

struct query {
	int x, y, v;
	query(int _x, int _y, int _v) {
		x = _x;
		y = _y;
		v = _v;
	}
};

vector <query> input;
int arb[maxn << 2];

inline void build(int node, int st, int dr) {
	if(st == dr) {
		arb[node] = a[st];
		return 0;
	}
	int mid = ((st + dr) >> 1);
	build(node << 1, st, mid);
	build((node << 1) | 1, mid + 1, dr);
	arb[node] = arb[node << 1] & arb[(node << 1) | 1];
}

inline int query(int node, int st, int dr, int a, int b) {
	if(a <= st && dr <= b)
		return arb[node];
	int mid = ((st + dr) >> 1);
	int ans = (1 << 32) - 1;
	if(a <= mid)
		ans = ans & query(node << 1, st, mid, a, b);
	if(mid < b)
		ans = ans & query((node << 1) | 1, mid + 1, dr, a, b);
	return ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("483d.in", "r", stdin);
	freopen("483d.out", "w", stdout);
	#endif

	cin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y, v;
		cin >> x >> y >> v;
		input.push_back(query(x, y, v));
		for(int bit = 0 ; bit < 30 ; ++ bit)
			if(v & (1 << bit)) {
				update(bit, x , 1);
				update(bit, y + 1, -1);
			}
	}
	for(int i = 1 ; i <= n ; ++ i) {
		for(int bit = 0 ; bit < 30 ; ++ bit) {
			int	sum = query(bit, i);
			if(sum > 0)
				a[i] |= (1 << bit);
		}
	}
	build(1, 1, n);
	for(int i = 0 ; i < input.size() ; ++ i)
		if(query(1, 1, n, input[i].x, input[i].y) != input[i].v) {
			cout << "NO\n";
			return 0;
		}
	cout << "YES\n";
	for(int i = 1 ; i <= n ; ++ i)
		cout << a[i] << ' ';
	
}
