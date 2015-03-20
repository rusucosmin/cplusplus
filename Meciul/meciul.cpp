#include <fstream>
#include <vector>
#include <string.h>
#include <iostream>

using namespace std;

const int maxn = 100005;

int where[maxn], t, n, m, where2[maxn];

int main() {
	ifstream fin("meciul.in");
	ofstream fout("meciul.out");
	fin >> t;
	while(t -- ) {
		memset(where, 0, sizeof(where));
		memset(where2, 0, sizeof(where2));
		fin >> n >> m;
		for(int i = 1 ; i <= m ; ++ i) {
			int x, y;
			fin >> x >> y;
//			cerr << x << ' ' << y << '\n';
//			for(int j = 1 ; j <= n ; ++ j)
//				cerr << where[j] << ' ';
//			cerr << '\n';
			if(where[x] && where[y]) {
				if(where[x] == where[y] && where2[x] == where2[y])
					fout << "NO\n";
				else
					fout << "YES\n";
				continue;
			}
			if(!where[x] && !where[y]) {
				where[x] = 1;
				where[y] = 2;
				where2[x] = 2;
				where2[y] = 1;
				fout << "YES\n";
				continue;
			}
			if(where[x]) {
				where[y] = 3 - where[x];
				where2[y] = 3 - where2[x];
				fout << "YES\n";
				continue;
			}
			if(where[y]) {
				where[x] = 3 - where[y];
				where2[x] = 3 - where2[y];
				fout << "YES\n";
			}
		}
	}
	
}
