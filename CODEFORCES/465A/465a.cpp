#include <iostream>
using namespace std;

const int maxn = 105;

int n;
char s[maxn];

int main() {
	cin >> n;
	cin >> s + 1;
	for(int i = 1 ; i <= n ; ++ i)
		if(s[i] == '0') {
			cout << i << '\n';
			return 0;
		}
	cout << n << '\n';
}
