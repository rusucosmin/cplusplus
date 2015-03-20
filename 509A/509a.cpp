#include <iostream>

using namespace std;

const int maxn = 1005;

int a[maxn][maxn], n;

int main() {
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= n ; ++ j)
			if(i == 1 || j == 1)
				a[i][j] = 1;
			else
				a[i][j] = a[i - 1][j] + a[i][j - 1];
	cout << a[n][n] << '\n';	
}
