#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

const int maxn = 120005;

int n, st[maxn];
pair<double, double> p[maxn];

inline long double crossproduct(pair<double, double> a, pair<double, double> b, pair<double, double> c) {
	return (b.first - a.first) * (c.second - a.second) - (c.first - a.first) * (b.second - a.second);
}

struct classcomp {
	inline bool operator () (const pair<double, double> &a, const pair<double, double> & b) const {
		return crossproduct(p[1], a, b) < 0;
	}
};

int main() {
	ifstream fin("infasuratoare.in");
	ofstream fout("infasuratoare.out");
	fin >> n;
	int ind = 1;
	for(int i = 1 ; i <= n ; ++ i) {
		fin >> p[i].first >> p[i].second;
		if(p[i] < p[ind])
			ind = i;
	}
	swap(p[1], p[ind]);
	sort(p + 2, p + n + 1, classcomp());
	st[++ st[0]] = 1;
	st[++ st[0]] = 2;
	for(int i = 3 ; i <= n ; ++ i) {
		while(st[0] >= 2 && crossproduct(p[st[st[0] - 1]], p[st[st[0]]], p[i]) > 0)
			-- st[0];
		st[++ st[0]] = i;
	}
	fout << st[0] << '\n';
	fout << fixed << setprecision(6);
	for(int i = st[0] ; i >= 1 ; -- i)
		fout << p[st[i]].first << ' ' << p[st[i]].second << '\n';
}
