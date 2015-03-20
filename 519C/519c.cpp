#include <iostream>

using namespace std;

int main() {
	int n, m, teams;
	cin >> n >> m;
	while(1) {
		if(!n || !m)
			break;
		if(n == 1 && m == 1)
			break;
		if(n >= m) {
			-- m;
			n -= 2;
		}
		else {
			-- n;
			m -= 2;
		}
		++ teams;
	}
	cout << teams << '\n';	
}
