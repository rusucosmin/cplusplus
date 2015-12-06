#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int maxn = 205;
const int mod = 98999;

int m, SI[maxn][maxn], SII[maxn][maxn];

int main() {
	ifstream fin("stirling.in");
	ofstream fout("stirling.out");

	SI[1][1] = 1;
	for(int i = 2 ; i < maxn ; ++ i)
		for(int j = 1 ; j <= i ; ++ j)
			SI[i][j] = (SI[i - 1][j - 1] - 1LL * (i - 1) * SI[i - 1][j]) % mod;	
	SII[1][1] = 1;
	for(int i = 2 ; i < maxn ; ++ i)
		for(int j = 1 ; j <= i ; ++ j)
			SII[i][j] = (SII[i - 1][j - 1] + 1LL * j * SII[i - 1][j]) % mod;
	fin >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y, z;
		fin >> x >> y >> z;
		if(x == 1)
			fout << SI[y][z] << '\n';
		else
			fout << SII[y][z] << '\n';
	}
}
