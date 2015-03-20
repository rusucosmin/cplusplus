#include <iostream>

using namespace std;

const int maxn = 1005;

char s[maxn];

int main() {
	cin >> s + 1;
	for(int i = 1 + (s[1] == '9') ; s[i] ; ++ i) {
		if(s[i] >= '5')
			s[i] = '9' - s[i] + '0';
	}
	cout << s + 1 << '\n';
}
