#include <iostream>
#include <vector>

using namespace std;

long long l, r, k, kpow = 1;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
	#endif
	cin >> l >> r >> k;
	vector <long long> v;
	v.push_back(1);
	for(int i = 0 ; kpow <= r / k ; ++ i) {
		kpow *= k;
		v.push_back(kpow);
	}
	bool ok = false;
	for(auto it : v) {
		if(it >= l) {
			cout << it << ' ';
			ok = true;
		}
	}
	if(!ok)
		cout << "-1\n";
}
