#include <fstream>
#include <iostream>

using namespace std;

int digit[20];

inline int number(bool type) {
	int x = 0;
	if(digit[digit[0]] == 0)
		if(type)
			return -1000000000;
		else
			return 1000000000;
	for(int i = digit[0] ; i >= 1 ; -- i)
		x = x * 10 + digit[i];
	return x;
}

inline int solve(int n, bool type) {
	int ans = n;	
	digit[0] = 0;
	while(n) {
		digit[++ digit[0]] = n % 10;
		n /= 10;
	}
	for(int i = 1 ; i <= digit[0] ; ++ i)
		for(int j = i + 1 ; j <= digit[0] ; ++ j) {
			swap(digit[i], digit[j]);
			if(type == 0)
				ans = min(ans, number(type));
			else
				ans = max(ans, number(type));
			swap(digit[i], digit[j]);
		}
	return ans;
}

int main() {
	ifstream fin("input.in");
	ofstream fout("output.out");

	int t;

	fin >> t;
	for(int i = 1 ; i <= t ; ++ i) {
		int n;
		fin >> n;
		fout << "Case #" << i << ": " << solve(n, 0) << ' ' << solve(n, 1) << '\n';
	}
	
}
