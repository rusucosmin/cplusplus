#include <fstream>
#include <string.h>
#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

const int maxn = 36; 
int main() {

int n, m, t;
long long g[maxn];
int clique[1 << (maxn / 2 + 1)];
bitset <maxn> a[maxn];


	ifstream fin("alianta.in");
	ofstream fout("alianta.out");
	fin >> t;
	while (t --) {
		fin >> n >> m;
		for(int i = 1 ; i <= m ; ++ i) {
			int x, y;
			fin >> x >> y;
			-- x; -- y;
			a[x][y] = 1;
			a[y][x] = 1;
		}
		for(int i = 0 ; i < n ; ++ i){
			g[i] = 0;
			for(int j = 0 ; j < n ; ++ j) {
				if(a[i][j] == 0 && i != j)
					g[i] |= (1LL << j);
				a[i][j] = 0;
			}

		}

		clique[0] = 0;

		int halfn = n >> 1;
		for(int conf = 1 ; conf < (1 << halfn) ; ++ conf) {
			clique[conf] = -1;
			bool isclique = true;
			int size = 0, maxi = 0;
			for(int i = 0 ; i < halfn ; ++ i)
				if(conf & (1 << i)) {
					++ size;
					if(isclique && ((conf & g[i]) != (conf ^ (1 << i))))
						isclique = false;
					maxi = max(maxi, clique[conf ^ (1 << i)]);
				}
			if(isclique)
				clique[conf] = size;
			else
				clique[conf] = maxi;
		}
		int ans = 0;	
		for(int conf = 1 ; conf < (1 << (n - halfn)) ; ++ conf) {
			bool isclique = true;
			int size = 0;
			int intersection = (1 << halfn) - 1;
			for(int i = 0 ; i < n - halfn && isclique ; ++ i) {
				if(conf & (1 << i)) {
					++ size;
					if(isclique && ((conf & (g[i + halfn] >> halfn)) != (conf ^ (1 << i))))
						isclique = false;
					intersection = intersection &  g[i + halfn];
				}
			}
			if(isclique)
				ans = max(ans, size + clique[intersection]);
		}
		fout << ans << '\n';
	}
}
