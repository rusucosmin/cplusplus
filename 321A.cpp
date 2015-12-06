#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

const int maxn = 100005;

int a[maxn], dp[maxn];
int n;

int main() {
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> a[i];
		if(i == 1)
			dp[i] = 1;
		else if(a[i - 1] <= a[i])
			dp[i] = dp[i - 1] + 1;
		else
			dp[i] = 1;
	}
	cout << *max_element(dp + 1, dp + n + 1) << '\n';
}
