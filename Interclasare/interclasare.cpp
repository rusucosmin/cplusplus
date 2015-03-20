#include <fstream>
#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

const int maxn = 10005;

int n, m;
int a[maxn], b[maxn];
int father[maxn];
int dp[maxn], l;
int lg;
bitset<maxn> useda, usedb;

int main() {
	ifstream fin("interclasare.in");
	ofstream fout("interclasare.out");

	fin >> n;
	for (int i = 1 ; i <= n ; ++ i)
		fin >> a[i];
	fin >> m;
	for (int i = 1 ; i <= m ; ++ i)
		fin >> b[i];

	dp[l = 0] = 0;
	lg = 1;
	for(int i = 1 ; i <= n ; ++ i) {
		while((lg << 1) <= l)
			lg <<= 1;
		int k = 0;
		
		for(int bit = lg ; bit ; bit >>= 1)
			if(k + bit <= l && a[ dp[k + bit] ] < a[i])
				k += bit;
		
		father[i] = dp[k];
		if(k == l)
			dp[++ l] = i;
		else
			if(a[ dp[k + 1] ] > a[i])
				dp[k + 1] = i;
	}
	int ans = l;
	int pos = dp[l];
	for(int i = 1 ; i <= l ; ++ i) {
		useda[pos] = 1;
		pos = father[pos];
	}

	dp[l = 0] = 0;
	lg = 1;
	for(int i = 1 ; i <= m ; ++ i) {
		while((lg << 1) <= i)
			lg <<= 1;
		int k = 0;

		for(int bit = lg ; bit ; bit >>= 1)
			if(k + bit <= l && b[ dp[k + bit] ] < b[i])
				k += bit;
		
		father[i] = dp[k];
		if(k == l)
			dp[++ l] = i;
		else
			if(b[ dp[k + 1] ] > b[i])
				dp[k + 1] = i;
	}

	ans += l;
	pos = dp[l];
	for(int i = 1 ; i <= l ; ++ i) {
		usedb[pos] = 1;
		pos = father[pos];
	} 
	fout << ans << '\n';
	
	int i = 1, j = 1;
	while(i <= n && j <= m) {
		while(i <= n && !useda[i]) {
			fout << a[i] << ' ';
			++ i;
		}
		while(j <= m && !usedb[j]) {
			fout << b[j] << ' ';
			++ j;
		}
		if(!useda[i] || !usedb[j])
			break;
		if(a[i] < b[j]) {
			fout << a[i] << ' ';
			++ i;
		}
		else {
			fout << b[j] << ' ';
			++ j;
		}
	}
	while(i <= n)
		fout << a[i++] << ' ';
	while(j <= m)
		fout << b[j++] << ' ';
	
	

}
