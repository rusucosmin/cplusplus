#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int n;

inline bool prime(int x) {
	for(int i = 2 ; i * i <= x ; ++ i)
		if(x % i == 0)
			return false;
	return true;	
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("472a.in", "r", stdin);
	freopen("472a.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 4 ; i <= n ; ++ i)
		if(!prime(i) && !prime(n - i)) {
			cout << i << ' ' << n - i << '\n';
			return 0;
		}
}
