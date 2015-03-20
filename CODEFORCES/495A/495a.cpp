#include <iostream>

using namespace std;

int cnt[] = {1, 6, 1, 2, 2, 3, 1, 4, 0, 1}; 

int main() {
	int n;
	cin >> n;
	cout << (cnt[n / 10] + 1) * (cnt[n % 10] + 1) << '\n';

}
