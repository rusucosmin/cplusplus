#include <fstream>
#include <iostream>

using namespace std;

const int maxn = 1005;

int n, p;
char s[maxn];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("465c.in", "r", stdin);
	freopen("465c.out", "w", stdout);
	#endif
	cin >> n >> p;
	cin >> s + 1;
	if(p == 1) {
		cout << "NO\n";
		return 0;
	}
	if(p == 2) {
		if(s[1] == 'a') {
			if(n == 1)
				cout << "b\n";
			else
				cout << "ba\n";
		}
		else
			cout << "NO\n";
		return 0;
	}
	int last = -1;
	char lastch;
	for(int i = n ; i >= 1 && last == -1 ; -- i) {
		for(char j = s[i] + 1 ; j <= p + 'a' - 1 ; ++ j)
			if(i == 1 || (i == 2 && j != s[i - 1]) || (i > 2 && j != s[i - 2] && j != s[i - 1])) {
				cerr << i << ' '<< j << '\n';
				last = i;
				lastch = j;
				break;
			}
	}
	if(last == -1) {
		cout << "NO\n";
		return 0;
	}
	s[last] = lastch;
	for(int i = last + 1 ; i <= n ; ++ i) {
		for(char j = 'a' ; j <= 'a' + p - 1 ; ++ j)
			if(i == 1 || (i == 2 && j != s[i - 1]) || (i > 2 && j != s[i - 2] && j != s[i - 1])) {
				s[i] = j;
				break;
			}
	}
	cout << s + 1 << '\n';
}
