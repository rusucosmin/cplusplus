#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

const int maxn = 2000005;

char s[maxn];
int a[maxn];
int n;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("525b.in", "r", stdin);
	freopen("525b.out", "w", stdout);
	#endif
	int m;
	cin >> s + 1;
	n = strlen(s + 1);
	cin >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x;
		cin >> x;
		a[x] ++;
		a[n - x + 1 + 1] --;
	}
	int sum = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		sum = sum + a[i];
		if(sum % 2 == 0)
			cout << s[i];
		else
			cout << s[n - i + 1];
	}
}
