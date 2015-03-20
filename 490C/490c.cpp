#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

const int maxn = 1000005;

int a, b, n, suffix[maxn], prefix[maxn];
char s[maxn];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("490c.in", "r", stdin);
	freopen("490c.out", "w", stdout);
	#endif
	cin.getline(s + 1, maxn);
	n = strlen(s + 1);
	cin >> a >> b;
	for(int i = 1 ; i <= n ; ++ i)
		prefix[i] = (prefix[i - 1] * 10 + s[i] - '0') % a;
	int P = 1;
	for(int i = n ; i >= 1 ; -- i) {
		suffix[i] = (suffix[i + 1] + P * (s[i] - '0')) % b;
		P = (P * 10) % b;
	}
	int pos = -1;
	for(int i = 1 ; i < n ; ++ i)
		if(prefix[i] == 0 && suffix[i + 1] == 0 && s[i + 1] != '0')
			pos = i;
	if(pos == -1) {
		cout << "NO\n";	
		return 0;
	}
	cout << "YES\n";
	char aux = s[pos + 1];
	s[pos + 1] = '\0';
	cout << s + 1 << '\n';
	s[pos + 1] = aux;
	cout << s + pos + 1 << '\n';
	
}
