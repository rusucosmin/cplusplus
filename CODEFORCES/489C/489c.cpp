#include <iostream>
#include <string.h>

using namespace std;

int m, sum;

inline bool can(int n, int actsum) {
	return 0 <= actsum && actsum <= 9 * n;
}

int main() {
	cin >> m >> sum;

	string minn = "";

	int auxsum = sum;
	for(int i = 1 ; i <= m ; ++ i) {
		for(int digit = 0 ; digit < 10 ; ++ digit) {
			if((i > 1 || digit > 0 || (m == 1 && digit == 0)) && can(m - i, auxsum - digit)) {
				auxsum -= digit;
				minn += (char)(digit + '0');
				break;
			}
		}
	}
	auxsum = sum;
	string maxx = "";
	for(int i = 1 ; i <= m ; ++ i) {
		for(int digit = 9 ; digit >= 0 ; -- digit) {
			if((i > 1 || digit > 0 || (m == 1 && digit == 0)) && can(m - i, auxsum - digit)) {
				auxsum -= digit;
				maxx += (char)(digit + '0');
				break;
			}
		}
	}
	if(minn.size() != maxx.size()) {
		cout << "-1 -1\n";
		return 0;
	}
	if(minn.size() != m) {
		cout << "-1 -1\n";
		return 0;
	}
	auxsum = 0;
	for(int i = 0 ; i < m ; ++ i)
		auxsum += (minn[i] - '0');
	if(auxsum != sum) {
		cout << "-1 -1\n";
		return 0;
	}
	auxsum = 0;
	for(int i = 0 ; i < m ; ++ i)
		auxsum += (maxx[i] - '0');
	if(auxsum != sum) {
		cout << "-1 -1\n";
		return 0;
	}
	cout << minn << ' ' << maxx << '\n';
}
