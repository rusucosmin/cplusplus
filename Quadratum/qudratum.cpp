#include <fstream>
#include <cassert>
#include <string.h>

using namespace std;

typedef long long Huge[1000];

ifstream fin("quadratum.in");
ofstream fout("quadratum.out");

Huge a;

void attrib(Huge h, long long val) {
	h[0] = 0;
	while (val > 0) {
		h[ ++ h[0] ] = val % 10;
		val /= 10;
	}
}

void multiply(Huge h, long long val) {
	long long T = 0;
	for(int i = 1 ; i <= h[0] ; ++ i) {
		h[i] = h[i] * val + T;
		T = h[i] / 10;
		h[i] %= 10;
	}
	while (T > 0) {
		h[ ++h[0] ] = T % 10;
		T /= 10;
	}
}

void divide(Huge h, long long val) {
	long long r = 0;
	for(int i = h[0] ; i >= 1 ; -- i) {
		h[i] = (r = 10 * r + h[i]) / val;
		r %= val;
	}
	while(!h[ h[0] ] && h[0] > 1)
		-- h[0];
	assert(r == 0);
}

int main() {
	int T;
	fin >> T;
	while(T -- ) {
		long long N;
		memset(a, 0, sizeof(a));
		fin >> N;
		attrib(a, N);
		multiply(a, N + 1);
		multiply(a, 2 * N + 1);
		divide(a, 6);
		for(int i = a[0] ; i >= 1 ; -- i)
			fout << a[i];
		fout << "\n";
	}
	
}
