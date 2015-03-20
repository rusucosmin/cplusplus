#include <fstream>
#include <vector>
#include <map>

using namespace std;

const int maxn = 2505;
const int maxk = 305;

int ans, n, k1, k2, values, a[maxn]; // k1 - crescatoare, k2 - descrescatoare
map <int, int> mymap;

class aint {
public:
	int arb[maxn << 2];
	aint() {
	}
	inline void update(int node, int st, int dr, int pos, int value) {
		if(st == dr) {
			arb[node] = max(arb[node], value);
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
		int ans = 0;
		if(a <= mid)
			ans = max(ans, query(node << 1, st, mid, a, b));
		if(mid < b)
			ans = max(ans, query((node << 1) | 1, mid + 1, dr, a, b));
		return ans;
	}
} arb[maxk][2];

int main() {
	ifstream fin("concert2.in");
	ofstream fout("concert2.out");

	fin >> n >> k1 >> k2;

	for(int i = 1 ; i <= n ; ++ i) {
		fin >> a[i];
		mymap[a[i]] = 0;
	}
	for(map<int, int> :: iterator it = mymap.begin() ; it != mymap.end() ; ++ it)
		mymap[it->first] = ++ values;
	ans = 1;
	int maxx = 0, x = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		for(int k = 2 ; k <= k1 ; ++ k) {
			x = 0;
			if(mymap[a[i]] != 1)
				x = arb[k - 1][0].query(1, 1, values, 1, mymap[a[i]] - 1);
			if(x) {
				ans = max(ans, x + 1);
				arb[k][0].update(1, 1, values, mymap[a[i]], x + 1);
			}
		}
		for(int k = 2 ; k <= k2 ; ++ k) {
			x = 0;
			if(mymap[a[i]] != values)
				x = arb[k - 1][1].query(1, 1, values, mymap[a[i]] + 1, values);
			if(x) {
				ans = max(ans, x + 1);
				arb[k][1].update(1, 1, values, mymap[a[i]], x + 1);
			}
		}
		arb[1][0].update(1, 1, values, mymap[a[i]], 1);
		arb[1][1].update(1, 1, values, mymap[a[i]], 1);
		if(k2 > 1) {
			maxx = 0;
			for(int k = 1 ; k <= k1 ; ++ k) {
				x = 0;
				if(mymap[a[i]] != values)
					x = arb[k][0].query(1, 1, values, mymap[a[i]] + 1, values);
				if(x)
					maxx = max(maxx, x + 1);
			}
			if(maxx) {
				ans = max(ans, maxx);
				arb[2][1].update(1, 1, values, mymap[a[i]], maxx);
			}
		}
		if(k1 > 1) {
			maxx = 0;
			for(int k = 1 ; k <= k2 ; ++ k) {
				x = 0;
				if(mymap[a[i]] != 1)
					x = arb[k][1].query(1, 1, values, 1, mymap[a[i]] - 1);
				if(x)
					maxx = max(maxx, x + 1);
			}
			if(maxx + 1) {
				arb[2][0].update(1, 1, values, mymap[a[i]], maxx);
				ans = max(ans, maxx);
			}
		}
		}
	fout << ans << '\n';
}
