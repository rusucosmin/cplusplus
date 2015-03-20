#include <fstream>
#include <iostream>

using namespace std;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("485c.in", "r", stdin);
	freopen("485c.out", "w", stdout);
	#endif

	int n;
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		long long l, r;
		cin >> l >> r;
		for(int j = 0 ; j < 63 ; ++ j)
			if(!(l & (1LL << j)) && (l | (1LL << j)) <= r)
				l |= (1LL << j);	
		cout << l << '\n';
	}
	
}
