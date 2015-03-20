#include <fstream>
#include <iostream>

using namespace std;

const int maxn = 100005;

map<string, int> mymap;
mymap<int, pair<string, string> > auxmap;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("499a.in", "r", stdin);
	freopen("499a.out", "w", stdout);
	#endif

	int n, x;
	cin >> n >> x;
	int actminute = 1;
	int ans = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		int l, r;
		cin >> l >> r;
		while(actminute + x <= l)
			actminute += x;
		while(actminute < l) {
			++ actminute;
			++ ans;
		}
		actminute = r + 1;
		ans += (r - l + 1);
	}
	cout << ans << '\n';
	
}
