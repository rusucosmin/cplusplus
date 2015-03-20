#include <iostream>

using namespace std;

int main() {
	int n, ans = 0;
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		int p, q;
		cin >> p >> q;
		if(q - p >= 2)
			++ ans;
	}
	cout << ans << '\n';
}
