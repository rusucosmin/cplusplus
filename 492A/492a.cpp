#include <fstream>
#include <iostream>

using namespace std;

int main() {
	int n, ans;
	long long sum = 0;
	cin >> n;
	for(int h = 1 ;  ; ++ h) {
		sum = sum + h;	
		if(n >= sum) {
			ans = h;
			n -= sum;
		}
		else {
			cout << h - 1 << '\n';
			break;
		}
	}
}
