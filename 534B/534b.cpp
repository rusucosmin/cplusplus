#include <iostream>
#include <fstream>

using namespace std;

int v1, v2, t, d;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("534b.in", "r", stdin);
	freopen("534b.out", "w", stdout);
	#endif
	cin >> v1 >> v2 >> t >> d;
	int total = v1;
	int actv = v1;
	for(int i = 2 ; i < t ; ++ i) {
		for(int delta = d ; delta >= -d ; -- delta) {
			if(actv + delta - (t - i) * d <= v2) {
				actv += delta;
				break;
			}
		}
		total += actv;
	}
	total += v2;
	cout << total << '\n';
}
