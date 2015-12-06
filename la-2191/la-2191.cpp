#include <string.h>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

const int maxn = 2000005;

int arb[maxn << 2], n, a[maxn];

inline void build(int node, int st, int dr) {
	if(st == dr) {
		arb[node] = a[st];
		return ;
	}
	int mid = ((st + dr) >> 1);
	build(node << 1, st, mid);
	build((node << 1) | 1, mid + 1, dr);
	arb[node] = arb[node << 1] + arb[(node << 1) | 1];
}

inline void update(int node, int st, int dr, int pos, int value) {
	if(st == dr) {
		arb[node] = value;
		return;
	}
	int mid = ((st + dr)>> 1);
	if(pos <= mid)
		update(node << 1, st, mid, pos, value);
	else
		update((node << 1) | 1, mid + 1, dr, pos, value);
	arb[node] = arb[node << 1] + arb[(node << 1) | 1];
}

inline int query(int node, int st, int dr, int a, int b) {
	if(a <= st && dr <=  b)
		return arb[node];
	int mid = ((st + dr) >> 1);
	int ans = 0;
	if(a <= mid)
		ans += query(node << 1, st, mid, a, b);
	if(mid < b)
		ans += query((node << 1) | 1, mid + 1, dr, a, b);
	return ans;
}

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void getint(int &x) {
	x = 0;
	while(!isdigit(buff[pos])) {
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}
	while(isdigit(buff[pos])) {
		x = x * 10 + buff[pos] - '0';
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}
}

inline void getstring(string &s) {
	s = "";
	while(!isalpha(buff[pos])) {
		if(++pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}
	while(isalpha(buff[pos])) {
		s = s + buff[pos];
		if(++ pos == lim) {
			pos = 0;
			fread(buff, 1, lim, stdin);
		}
	}
}


int main() {
	#ifndef ONLINE_JUDGE
	freopen("la-2191.in", "r", stdin);
	freopen("la-2191.out", "w", stdout);
	#endif
	int test = 0;
	while(true) {
		getint(n);
		if(n == 0)
			return 0;
		if(test)
			cout << "\n";
		cout << "Case " << ++ test << ":\n";
		for(int i = 1 ; i <= n ; ++ i)
			getint(a[i]);
		build(1, 1, n);
		while(true) {
			string s; int x, y;
			getstring(s);
			if(s == "END")
				break;
			getint(x); getint(y);
			if(s[0] == 'M')
				cout << query(1, 1, n, x, y) << '\n';
			else
				update(1, 1, n, x, y);
		}
	}
	
}
