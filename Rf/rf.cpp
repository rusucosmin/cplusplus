#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

ifstream fin("rf.in");
ofstream fout("rf.out");

const int maxn = 305;
const int oo = 0x3f3f3f3f;

int n, rf[maxn][maxn], d[maxn][maxn];

int main() {
	fin >> n;
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= n ; ++ j) {
			fin >> rf[i][j]; 
			if(i == j)
				continue;
			if(!rf[i][j]) {
				rf[i][j] = oo;
				d[i][j] = 0;
			}
			else
				d[i][j] = 1;
		}
	for(int k = 1 ; k <= n ; ++ k)
		for(int i = 1 ; i <= n ; ++ i)
			for(int j = 1 ; j <= n ; ++ j)
				if(rf[i][j] > rf[i][k] + rf[k][j]) {
					rf[i][j] = rf[i][k] + rf[k][j];
					d[i][j] = d[i][k] + d[k][j];
				}
				else if(rf[i][j] == rf[i][k] + rf[k][j])
					d[i][j] = max(d[i][j], d[i][k] + d[k][j]);
	for(int i = 1 ; i <= n ; ++ i, fout << '\n')
		for(int j = 1 ; j <= n ; ++ j)
			fout << rf[i][j] << ' ';
	for(int i = 1 ; i <= n ; ++ i, fout << '\n')
		for(int j = 1 ; j <= n ; ++ j)
			fout << d[i][j] << ' ';
}
