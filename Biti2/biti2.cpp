#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <cassert>

using namespace std;

ifstream fin("biti2.in");
ofstream fout("biti2.out");

const int maxn = 5515;
const int base = 10;

char x[maxn], k[maxn];
int n;

inline void multiply(char mare[], int k) {
	int t = 0;	
	for(int i = 1 ; i <= mare[0] ; ++ i) {
		mare[i] = mare[i] * k + t;			
		t = mare[i] / base;
		mare[i] %= base;
	}
	while(t) {
		mare[++ mare[0] ] = t % base;
		t /= base;
	}
}

inline int divide(char mare[], int k) {
	int r = 0;
	for(int i = mare[0] ; i >= 1 ; -- i) {
		mare[i] = (r = r * base + mare[i]) / k;
		r %= k;
	}
	while(!mare[mare[0]] && mare[0])
		-- mare[0];
	return r;
}

inline int compare(char a[], char b[]) {
	if(a[0] > b[0])
		return -1;
	if(a[0] < b[0])
		return 1;
	for(int i = a[0] ; i >= 1 ; -- i) {
		if(a[i] > b[i])
			return -1;
		if(a[i] < b[i])
			return 1;
	}
	return 0;
}

inline void subtract(char a[], char b[]) {
	int t = 0;
	for(int i = b[0] + 1 ; i <= a[0] ; )
		b[i ++] = 0;
	for(int i = 1 ; i <= a[0] ; ++ i) {
		a[i]+= (t=(a[i]-=b[i]+t)<0) ? 10 : 0;
	}
	while(!a[a[0]] && a[0])
		-- a[0];
}

int power;

inline void print(char x[]) {
	fout << (int)x[0] << ": ";
	if(x[0] <= 0)
		return;
	for(int i = x[0] ; i >= 1 ; -- i)
		fout << (int)x[i] << ' ';
	fout << '\n';
}

inline bool isone(char x[]) {
	if(x[0] == 1 && x[1] == 1)
		return true;
	return false;
}

inline bool iszero(char x[]) {
	if(x[0] == 1 && x[1] == 0)
		return true;
	if(x[0] == 0)
		return true;
	return false;
}

inline void debug(string s) {
	fout << s;
	print(x);
	print(k);
}

inline bool solve() {
	if(isone(x))
		return 1;
	if(iszero(x))
		return 0;
	if(x[0] < 0 || k[0] < 0)
		assert(false);
	while(compare(k, x) == -1)
		divide(k, 2);
	subtract(x, k);
	return !solve();
}

int main() {
	fin >> n;
	fin.get();
	for(int i = 1 ; i <= n ; ++ i) {
		k[0] = 1;
		k[1] = 1;
		fin.getline(x + 1, maxn);
		x[0] = strlen(x + 1);
		reverse(x + 1, x + x[0] + 1);
		for(int j = 1 ; j <= x[0] ; ++ j)
			x[j] -= '0';
		while(compare(k, x) != -1)
			multiply(k, 2);
		/// compare(k, x) == -1, deci e strict mai mare
		fout << solve() << '\n';
	}
}
