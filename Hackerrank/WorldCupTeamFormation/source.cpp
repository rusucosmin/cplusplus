#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	vector <int> v;
	for(int i = 0 ; i < 10 ; ++ i) {
		int x;
		cin >> x;
		v.push_back(x);
	}
	sort(v.begin(), v.end(), greater <int> ());
	cout << v[0] + v[2] + v[4] << '\n';
	
}
