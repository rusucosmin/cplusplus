#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 3005;

int n, a[maxn];

int main() {
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> a[i];
	cout << n << '\n';
	for(int i = 1 ; i <= n ; ++ i) {
		int minindex = i;
		for(int j = i + 1 ; j <= n ; ++ j)
			if(a[minindex] > a[j])
				minindex = j;
		swap(a[minindex], a[i]);
		cout << i - 1 << ' ' << minindex - 1 << '\n';
	}
}

