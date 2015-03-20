#include <iostream>
#include <fstream>
#include <set>

using namespace std;

int w, h, n;
multiset <int> rx, ry;
multiset <int> distx, disty;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("528a.in", "r", stdin);
	freopen("528a.out", "w", stdout);
	#endif

	cin >> w >> h >> n;
	rx.insert(0);
	rx.insert(w);
	ry.insert(0);
	ry.insert(h);
	distx.insert(-w);
	disty.insert(-h);
	for(int i = 1 ; i <= n ; ++ i) {
		char op; int x;
		cin >> op >> x;
		if(op == 'V') {
			auto p1 = rx.lower_bound(x);
			auto p2 = rx.lower_bound(x);
			if(p1 != rx.begin())
				-- p1;
	//		cout << "x \n";
	//		cout << *p1 << ' ' << *p2 << '\n';
			rx.insert(x);
			distx.erase(distx.find(-(*p2 - *p1)));
			distx.insert(-(x - *p1));
			distx.insert(-(*p2 - x));
			cout << 1LL * (*distx.begin()) * (*disty.begin()) << '\n';
		}
		else {
			auto p1 = ry.lower_bound(x);
			auto p2 = ry.lower_bound(x);
			if(p1 != ry.begin())
				-- p1;
	//		cout << "y \n";
	//		cout << *p1 << ' ' << *p2 << '\n';
			ry.insert(x);
			disty.erase(disty.find(-(*p2 - *p1)));
			disty.insert(-(x - *p1));
			disty.insert(-(*p2 - x));
			cout << 1LL * (*distx.begin()) * (*disty.begin()) << '\n';
		}
	}
	
}
