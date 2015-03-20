#include <fstream>
#include <vector>
#include <unordered_map>
#include <bitset>
#include <iostream>

using namespace std;

const int maxn = 1000000005;
const int maxp = 1000005;

ifstream fin("perioada01.in");
ofstream fout("perioada01.out");

int n, m, dif[maxp], p[maxp], pi[maxp];

#define debug

int main() {
	fin >> n >> m >> p[1];
	for(int i = 2 ; i <= m ; ++ i) {
		fin >> p[i];
		dif[i - 1] = p[i] - p[i - 1];
	}
	dif[m] = n + p[1] - p[m];
	
	int k = 0;
	for(int i = 2 ; i <= m ; ++ i) {
		while(k > 0 && dif[k + 1] != dif[i])
			k = pi[k];
		if(dif[k + 1] == dif[i])
			++ k;
		pi[i] = k;
	}
	int ans = -1;
/*
	for(int period = pi[m] ; period != 0 ; period = pi[period]) {
		if(m % (m - period) == 0)
			ans = m - period;
	}
*/
	if(m % (m - pi[m]) == 0)
		ans = m - pi[m];
	if(ans <= 0) {
		fout << ans << '\n';
		return 0;
	}
	int sum = 0;
	for(int i = 1 ; i <= ans ; ++ i)
		sum += dif[i];
	fout << sum << '\n';
	return 0;

}
