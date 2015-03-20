#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

const int maxn = 2000005;

string a, b, t;
int n, m, q, zdr[maxn], zst[maxn];

inline int expand(int x, int y) {
	int ret = 0;
	for(int i = x, j = y ; j < t.size() ; ++i, ++ j) {
		if(t[i] != t[j])
			return ret;
		++ ret;
	}
	return ret;
}

inline void preprocessz(int *z) {
	int l = -1, r = -1;
	z[0] = t.size();
	for(int i = 1 ; i < t.size() ; ++ i) {
		if(i > r) {
			z[i] = expand(0, i);
			if(z[i] != 0) {
				l = i;
				r = i + z[i] - 1;
			}
		}
		else {
			int k = i - l;	
			int b = r - i + 1;
			if(z[k] < b) {
				z[i] = z[k];
				continue;
			}
			z[i] = b + expand(b, r + 1);
			if(i + z[i] - 1 > r) {
				l = i;
				r = i + z[i] - 1;
			}
		}
	}
}

int main() {
	ifstream fin("x.in");
	ofstream fout("x.out");

	fin >> n >> m >> q;
	fin.get();
	getline(fin, a);
	getline(fin, b);
	t = b + a;
	preprocessz(zdr);
	reverse(a.begin(), a.end());
	t = b + a;
	preprocessz(zst);

	reverse(zst + b.size(), zst + t.size());

	/*
	for(int i = 0 ; i < t.size() ; ++ i)
		fout << zdr[i] << ' ';
	fout << '\n';
	for(int i = 0 ; i < t.size() ; ++ i) {
		fout << zst[i] << ' ';
	}
	fout << '\n';
	*/

	for(int i = 0 ; i < q ; ++ i) {
		int x, y;
		fin >> x >> y;
		x += b.size();
		y += b.size();
		x -= 2;
		int lf = 0, rf = 0;
		if(x < b.size())
			lf = 0;	
		else
			lf = zst[x];
		if(y == t.size())
			rf = 0;
		else
			rf = zdr[y];
		fout << min(int(b.size()), min(lf, rf)) << '\n';
	}

}
