#include <fstream>
#include <unordered_map>
#include <iostream>
#include <stdlib.h>

using namespace std;

const int maxn = 100005;

int n, l, a[maxn], x, y;
unordered_map<int, bool> mymap;

inline void trytoput(int where, int dist) {
	if(mymap[where - dist] || mymap[where + dist]) {
		cout << "1\n" << where << '\n';
		exit(0);
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("479d.in", "r", stdin);
	freopen("479d.out", "w", stdout);
	#endif

	cin >> n >> l >> x >> y;
	bool hasx = false, hasy = false;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> a[i];
		mymap[a[i]] = 1;
		if(mymap[a[i] - x])
			hasx = 1;
		if(mymap[a[i] - y])
			hasy = 1;
	}
	if(hasx && hasy) {
		cout << "0\n";
		return 0;
	}
	if(hasx) {
		cout << "1\n" << y << '\n';
		return 0;
	}
	if(hasy) {
		cout << "1\n" << x << '\n';
		return 0;
	}
	for(int i = 1 ; i <= n ; ++ i) {
		if(a[i] - x >= 0)
			trytoput(a[i] - x, y);
		if(a[i] + x <= l)
			trytoput(a[i] + x, y);
		if(a[i] - y >= 0)
			trytoput(a[i] - y, x);
		if(a[i] + y <= l)
			trytoput(a[i] + y, x);
	}
	cout << "2\n" << x << ' ' << y << '\n';
}
