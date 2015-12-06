#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("534a.in", "r", stdin);
	freopen("534a.out", "w", stdout);
	#endif
	int n;
	cin >> n;
	vector <int> v[2];
	for(int i = 1 ; i <= n ; ++ i) {
		v[i % 2].push_back(i);
	}
	if(n == 3) {
		cout << "2\n1 3\n";	
		return 0;
	}
	if(n <= 2) {
		cout << "1\n1\n";
		return 0;
	}
	if(n == 4) {
		cout << "4\n2 4 1 3\n";
		return 0;
	}
	cout << n << '\n';
	for(auto it : v[0]) {
		cout << it << ' ';
	}
	for(auto it : v[1])
		cout << it << ' ';
	return 0;
}
