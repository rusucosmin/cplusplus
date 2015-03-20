#include <fstream>
#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

const int maxn = 105;

int n, m, a[maxn], b[maxn];

int main() {
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> a[i];
	cin >> m;
	for(int j = 1 ; j <= m ; ++ j)
		cin >> b[j];

	sort(a + 1, a + n + 1);
	sort(b + 1, b + m + 1);

	int ans = 0;
	
	for(int i = 1 ; i <= n ; ++ i) {
		for(int j = 1 ; j <= m ; ++ j) {
			if(abs(a[i] - b[j]) <= 1) {
				++ ans;
				b[j] = 0x3f3f3f3f;
				break;
			}
		}
	}
	cout << ans << '\n';	
}
