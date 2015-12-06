#include <iostream>

using namespace std;

int main() {
	int xorsum = 0;
	for(int i = 1 ; i <= 100 ; ++ i) {
		xorsum = xorsum ^ i;
		cout << i << " = " << xorsum << '\n';
	}
}
