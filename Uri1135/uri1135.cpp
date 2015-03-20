#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 100005;
const int maxl = 20;

int n, q, ancestor[maxl][maxn], level[maxn];
long long sum[maxl][maxn]; 

inline long long path(int x, int y) {
	if(level[x] < level[y])
		swap(x, y);
	int log1, log2;
	long long s = 0;
	for(log1 = 1; (1 << log1) < level[x] ; ++ log1);
	for(log2 = 1; (1 << log2) < level[x] ; ++ log2);
	for(int k = log1 ; k >= 0 ; -- k)
		if(level[x] - (1 << k) >= level[y]) {
			s += sum[k][x];
			x = ancestor[k][x];
		}
	if(x == y)
		return s;
	for(int k = log2 ; k >= 0 ; -- k)
		if(ancestor[k][x] != ancestor[k][y]) {
			s += sum[k][x];
			s += sum[k][y];
			x = ancestor[k][x];
			y = ancestor[k][y];
		}
	return s + sum[0][x] + sum[0][y];
}

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void getint(int &x) {
	x = 0;
	while(!isdigit(buff[pos]))
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	while(isdigit(buff[pos])) {
		x = x * 10 + buff[pos] - '0';
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}

}


inline void getint(long long &x) {
	x = 0LL;
	while(!isdigit(buff[pos]))
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	while(isdigit(buff[pos])) {
		x = x * 10LL + buff[pos] - '0';
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}

}

int main() {
	#ifndef ONLINE_JUDGE
		freopen("uri1135.in", "r", stdin);
		freopen("uri1135.out", "w", stdout);
	#endif
	while(true) {
		getint(n);
		if(n == 0)
			break;
		level[0] = 1;
		for(int i = 1 ; i < n ; ++ i) {
			getint(ancestor[0][i]);
			getint(sum[0][i]);
			level[i] = level[ancestor[0][i]] + 1;
		}
		for(int k = 1 ; (1 << k) <= n ; ++ k)
			for(int i = 0 ; i < n ; ++ i) {
				ancestor[k][i] = ancestor[k - 1][ancestor[k - 1][i]];
				sum[k][i] = sum[k - 1][i] + sum[k - 1][ancestor[k - 1][i]];
			}
		getint(q);
		while (q --) {
			int x, y;
			getint(x);
			getint(y);
			cout << path(x, y);
			if(q)
			cout << ' ';
		}
		cout << '\n';
	}

}
