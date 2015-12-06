#include <iostream>
#include <vector>
#include <bitset>
#include <cassert>
#include <unordered_map>

using namespace std;

const int maxn = 105;

int n, a[maxn], cnt, v[maxn];
unordered_map<int, int> mymap[maxn], secondmap;

int main() {
	#ifdef HOME
		freopen("intput.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> a[i];
		v[i] = a[i];
	}

	int	sz1 = (n + 1) / 2;
	mymap[0][0] = 1;
	for(int i = 1 ; i <= sz1 ; ++ i) {
		int maxmask = (1 << (i - 1));
		for(int conf = 0 ; conf < maxmask ; ++ conf) {
			for(int j = 0 ; j < i - 1 ; ++ j) {
				if(conf & (1 << j)) {
					v[j + 2] += v[j + 1];
					v[j + 1] = 0;
				}
			}
			int xorsum = 0;
			for(int j = 1 ; j <= i ; ++ j) {
				xorsum = xorsum ^ v[j];	
				v[j] = a[j];
			}
			++ mymap[i][xorsum];
		}
	}

	int sz2 = n - sz1;
	int maxmask = (1 << sz2);	
	long long ans = 0;
	for(int mask = 0 ; mask < maxmask ; ++ mask) {
		vector <int> act;
		for(int i = 0 ; i + 1 < sz2 ; ++ i)
				if(mask & (1 << i)) {
					v[sz1 + i + 2] += v[sz1 + i + 1];
					v[sz1 + i + 1] = 0;
				}
		int fullxorsum = 0;
		act.clear();
		for(int i = sz1 + 1 ; i <= n ; ++ i) {
			if(v[i]) {
				act.push_back(v[i]);
				fullxorsum ^= v[i];
			}
			v[i] = a[i];
		}
		if(mask & (1 << (sz2 - 1))) {
			int sum = 0;
			for(int i = sz1 ; i >= 1 ; -- i) {
				sum += a[i];	
				int actxor = fullxorsum ^ act[0];
				actxor ^= (sum + act[0]);
				ans += mymap[i-1][actxor];
			}
		}
		else {
			ans += mymap[sz1][fullxorsum];	
		}
		for(int i = 1 ; i <= n ; ++ i)
			v[i] = a[i];
	}
	cout << ans << '\n';
}
