#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <cassert>
#include <iostream>

using namespace std;

const int maxn = 1001;
const int maxlg = 10;

short rmq[2][maxn][maxlg][maxn], lg[maxn];
char s[maxn + 10][maxn + 10];
short n, m;

inline void Manacher(short i, short whichp) {
	short best = 0, ind = 0, j;
	for(j = 1 ; j <= n ; ++ j) {
		if(j <= best)
			rmq[whichp][j][0][i] = min((short)(best - j), rmq[whichp][2 * ind - 1][0][i]);
		short &aux = rmq[whichp][j][0][i];
		while(j - aux - 1 >= 1 && j + aux + 1 <= n
		&& s[i][j - aux - 1] == s[i][j + aux + 1])
			++ aux;
		if(j + aux > best) {
			best = j + aux;
			ind = j;
		}
	}
}

inline void buildrmq(short ind) {
	short j, l, i, aux;
	for(j = 1 ; j <= n ; ++ j) {
		for(l = 1 ; (1 << l) <= n ; ++ l)	 {
			aux = (1 << (l - 1));
			for(i = 1 ; i + (1 << l) - 1 <= n ; ++ i) {
				rmq[ind][j][l][i] = rmq[ind][j][l - 1][i];
				if(rmq[ind][j][l][i] > rmq[ind][j][l - 1][i + aux])
					rmq[ind][j][l][i] = rmq[ind][j][l - 1][i + aux];
			}
		}
	}
}

inline short queryrmq(short ind, short col, short x, short y) {
	int log = lg[y - x + 1];
	int ret = rmq[ind][col][log][x];
	if(ret > rmq[ind][col][log][y - (1 << log) + 1])
		ret = rmq[ind][col][log][y - (1 << log) + 1];
	return ret;
}

inline short binarysearch(short x, short y) {
	short ls = min(rmq[0][y][0][x], rmq[1][x][0][y]);
	short ret = 0;
	for(short k = lg[ls] + 1; k >= 0 ; -- k)
		if(ret + (1 << k) <= ls && queryrmq(0, y, x - ret - (1 << k), x + ret + (1 << k)) >= ret + (1 << k)
		&& queryrmq(1, x, y - ret - (1 << k), y + ret + (1 << k)) >= ret + (1 << k))
			ret += (1 << k);
	return ret + 1;
}

int main() {
	freopen("pscpld2d.in", "r", stdin);
	freopen("pscpld2d.out", "w", stdout);
	
	short i, j;

	scanf("%hd", &n);
	for(i = 1 ; i <= n ; ++ i) {
		scanf("%s", s[i] + 1);
		Manacher(i, 0);
	}
	buildrmq(0);
	for(i = 1 ; i <= n ; ++ i) {
		for(j = i + 1 ; j <= n ; ++ j)
			swap(s[i][j], s[j][i]);
		Manacher(i, 1);
	}

	buildrmq(1);
	for(i = 2 ; i <= n ; ++ i)
		lg[i] = 1 + lg[i >> 1];

	int ans = 0;
	
	for(i = 1 ; i <= n ; ++ i)
		for(j = 1 ; j <= n ; ++ j)
			ans = ans + binarysearch(i, j);
	printf("%d\n", ans);
}
