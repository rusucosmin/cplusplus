#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

const int maxn = 1005;

int n, a[maxn];

int main() {
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> a[i];
	sort(a + 1, a + n + 1);
	if(a[1] == 1)
		cout << "-1\n";
	else
		cout << "1\n";
}
