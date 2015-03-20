#include <iostream>

using namespace std;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("495b.in", "r", stdin);
	freopen("495b.out", "w", stdout);
	#endif
	int a, b;
	cin >> a >> b;
	int diff = a - b;
	if(diff == 0) {
		cout << "infinity\n";
		return 0;
	}
	if(diff < 0) {
		cout << "0\n";
		return 0;
	}
	int aux = diff;
	int ans = 0;
	for(int div = 1 ; div * div <= aux ; ++ div) {
		if(diff % div == 0) {
			if((a / div) * div == diff)
				++ ans;
			int div2 = diff / div;
			if(div == div2)
				continue;
			if((a / div2) * div2 == diff)
				++ ans;
		}
	}
	cout << ans << '\n';
}
