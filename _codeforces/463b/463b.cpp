#include <iostream>

using namespace std;

int main() {
	int n, lastx = 0, energy = 0;
	cin >> n;
	int ans = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		int x;
		cin >> x;
		energy += (lastx - x);
		if(energy < 0) {
			ans += -energy;	
			energy = 0;
		}
		lastx = x;
	}
	cout << ans << '\n';
}
