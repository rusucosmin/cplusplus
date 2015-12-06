#include <fstream>
#include <iostream>

using namespace std;

const int maxn = 105;
const int oo = 0x3f3f3f3f;

ifstream fin("royfloyd.in");
ofstream fout("royfloyd.out");

int rf[maxn][maxn], n;

int main() {
	fin >> n;
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= n ; ++ j) {
			fin >> rf[i][j];
			if(i == j)
				continue;
			if(!rf[i][j])
				rf[i][j] = oo;
		}
	for(int k = 1 ; k <= n ; ++ k)
		for(int i = 1 ; i <= n ; ++ i)
			for(int j = 1 ; j <= n ; ++ j)
				rf[i][j] = min(rf[i][j], rf[i][k] + rf[k][j]);
	for(int i = 1 ; i <= n ; ++ i, fout << '\n')
		for(int j = 1 ; j <= n ; ++ j) {
			if(rf[i][j] == oo)
				rf[i][j] = 0;
			fout << rf[i][j] << ' ';
		}
}

