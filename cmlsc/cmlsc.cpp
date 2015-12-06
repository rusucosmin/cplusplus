#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

vector <int> cmlsc(vector <int> a, vector <int> b) {
	int dp[a.size() + 1][b.size() + 1];
	int n = a.size();
	int m = b.size();
	memset(dp, 0, sizeof(dp));
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= m ; ++ j)
			if(a[i - 1] == b[j - 1])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

	int i = n, j = m;
	vector <int> v;
	while(i > 0 && j > 0) {
		if(a[i - 1] == b[j - 1]) {
			v.push_back(a[i - 1]);
			-- i;
			-- j;
		}
		else if(dp[i][j - 1] <= dp[i - 1][j])
			-- i;
		else
			-- j;
	}
	reverse(v.begin(), v.end());
	return v;
}

int arr[100];

int main() {
	ifstream fin("cmlsc.in");
	ofstream fout("cmlsc.out");

	int n, m;
	fin >> n >> m;
	vector <int> a, b;
	for(int i = 0 ; i < n ; ++ i) {
		int x;
		fin >> x;
		a.push_back(x);
	}
	for(int i = 0 ; i < m ; ++ i) {
		int x;
		fin >> x;
		b.push_back(x);
	}
	vector <int> v = cmlsc(a, b);
	fout << v.size() << '\n';
	for(auto it : v)
		fout << it << ' ';
}
