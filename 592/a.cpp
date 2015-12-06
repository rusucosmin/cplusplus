#include <iostream>
#include <bitset>

using namespace std;

const int maxn = 8;
const int inf = 0x3f3f3f3f;

char a[maxn][maxn];
bitset <maxn> hasB, hasW;

int getDist(int i, int j, int d) {
	int rasp = 0;
	while(i + 1 < 8 && i > 0 && a[i + d][j] == '.')
		i += d,
		rasp ++;
	if(d == -1 && i == 0)
		return rasp;
	if(d == 1 && i == 7)
		return rasp;
	return inf;
}

int main() {
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	for(int i = 0 ; i < 8 ; ++ i)
		for(int j = 0 ; j < 8 ; ++ j)
			cin >> a[i][j]; 
	
	int answ = inf, ansb = inf;

	for(int i = 0 ; i < 8 ; ++ i)
		for(int j = 0 ; j < 8 ; ++ j) {
			if(a[i][j] == 'W') {
				int dist = getDist(i, j, -1);
				answ = min(answ, dist);
			}
			if(a[i][j] == 'B') {
				int dist = getDist(i, j, 1);
				ansb = min(ansb, dist);
			}
		}
	if(answ <= ansb) {
		cout << 'A' << '\n';
	}
	else
		cout << 'B' << '\n';
}
