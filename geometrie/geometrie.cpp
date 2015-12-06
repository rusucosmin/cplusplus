#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>

using namespace std;

const int maxn = 100005;

int n, m, st[maxn], top;
pair<int, int> p[maxn], aux[maxn];
long long sum[maxn], revsum[maxn];
map<pair<int, int>, int> mymap;

inline long long crossproduct(pair<int, int> a, pair<int, int> b, pair<int, int> c) {
	return 1LL * (b.first - a.first) * (c.second - a.second) - 1LL * (c.first - a.first) * (b.second - a.second);
}

struct classcomp {
	inline bool operator () (const pair<int, int> &a, const pair<int, int> &b) const {
		return crossproduct(p[1], a, b) > 0;
	}
};

inline long long area(vector <pair<int, int> > a) {
	a.push_back(*a.begin());
	long long aria = 0;
	for(int i = 0 ; i + 1 < a.size() ; ++ i)
		aria = (aria + 1LL * a[i].first * a[i + 1].second - 1LL * a[i + 1].first * a[i].second);
	return aria;
}

int main() {
	ifstream fin("geometrie.in");
	ofstream fout("geometrie.out");
	fin >> n >> m;
	int ind = 1;
	for(int i = 1  ; i <= n ; ++ i) {
		fin >> p[i].first >> p[i].second;
		if(p[ind] > p[i])
			ind = i;
	}
	swap(p[ind], p[1]);
	sort(p + 2, p + n + 1, classcomp());
	st[++ top] = 1;
	st[++ top] = 2;
	for(int i = 3 ; i <= n ; ++ i) {
		while(top >= 2 && crossproduct(p[st[top - 1]], p[st[top]], p[i]) < 0)
			-- top;
		st[++ top] = i;
	}
	st[top + 1] = st[1];

	for(int i = 1 ; i <= top ;++ i) {
		sum[i] = sum[i - 1] + 1LL * p[st[i]].first * p[st[i + 1]].second - 1LL * p[st[i + 1]].first * p[st[i]].second;
		mymap[p[st[i]]] = i;
		aux[i] = p[st[i]];
	}
	for(int i = 1 ; i <= top ; ++ i)
		revsum[i] = sum[top] - sum[i - 1];
	sort(aux + 1, aux + top + 1);
	for(int i = 1 ; i <= m ; ++ i) {	
		int qx, qy;
		fin >> qx >> qy;
		auto aux = mymap.upper_bound(make_pair(qx, qy));
		auto bux = mymap.lower_bound(make_pair(qx, qy));
		cout << aux->second << ' ' << bux->second << '\n';
		fout << sum[aux->second] + revsum[top - bux->second + 1] + 1LL * aux->first *  << '\n';
	}
}
