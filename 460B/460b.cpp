#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

inline int sum_digit(long long x) {
	if(x == 0)
		return 0;
	return x % 10 + sum_digit(x / 10);
}

int main() {
	int a, b, c;
	cin >> a >> b >> c;
	vector <long long> ans;
	for(int i = 1 ; i <= 81 ; ++ i) {
		long long p = 1;
		for(int j = 1 ; j <= a ; ++ j)
			p *= i;
		p *= b;
		p += c;
		if(p < 1000000000 && sum_digit(p) == i)
			ans.push_back(p);
	}
	cout << ans.size() << '\n';
	for(auto it:ans)
		cout << it << ' ';
}
