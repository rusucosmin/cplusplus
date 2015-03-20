#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 200005;

int n, m, father[maxn];
vector <pair<int, pair<int, int> > > v;

inline int find(int x) {
	if(x != father[x])
		father[x] = find(father[x]);
	return father[x];
}

int main() {
	ifstream fin("apm.in");
	ofstream fout("apm.out");

	fin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x, y, z;
		fin >> x >> y >> z;
		v.push_back(make_pair(z, make_pair(x, y)));
	}
	for(int i = 1 ; i <= n ; ++ i)
		father[i] = i;
	sort(v.begin(), v.end());
	vector <pair<int, int> > apm;
	int total = 0;
	for(int i = 0 ; i < v.size() ; ++ i){
		int tx = find(v[i].second.first);
		int ty = find(v[i].second.second);
		if(tx == ty)
			continue;
		father[tx] = ty;
		total += v[i].first;
		apm.push_back(v[i].second);
	}
	fout << total << '\n' << n - 1 << '\n';
	for(int i = 0 ; i < apm.size() ; ++ i)
		fout << apm[i].first << ' ' << apm[i].second << '\n';
}
