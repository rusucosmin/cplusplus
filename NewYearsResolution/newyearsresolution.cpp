#include <fstream>
#include <iostream>

using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

const int maxn = 22;

int t, n, a[maxn], b[maxn], c[maxn], x, y, z;

inline string solve() {
	for(int conf = 0 ; conf < (1 << n) ; ++ conf) {
		int actx = 0, acty = 0, actz = 0;
		for(int i = 0 ; i < n ; ++ i) {
			if(conf & (1 << i)) {
				actx += a[i];
				acty += b[i];
				actz += c[i];
			}
		}
		if(actx == x && acty == y && actz == z)
			return "yes";
	}
	return "no";
}

int main() {
	fin >> t;
	for(int i = 1 ; i <= t ; ++ i) {
		fin >> x >> y >> z;
		fin >> n;
		for(int i = 0 ; i < n ; ++ i)
			fin >> a[i] >> b[i] >> c[i];	
		fout << "Case #" << i << ": " << solve() << '\n';
	}
}
