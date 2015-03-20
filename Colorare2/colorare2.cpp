#include <fstream>
#include <iostream>
#include <string.h>
#include <bitset>
#include <vector>

using namespace std;

const int maxn = 205;
const int maxk = 2505;

bitset< maxk > used;
int n, m, k, p, col[maxk], a[maxk], b[maxk];
vector <pair<int, int> > g[maxn];

inline int getcolor(int node) {
	used.reset();
	for(vector <pair<int, int> > :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
		used[col[it->second]] = 1;
	for(int i = 1 ; i <= p + 1 ; ++ i)
		if(!used[i])
			return i;
}

inline void paint(int node, int ca, int cb) {
	for(vector <pair<int, int> > :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
		if(col[it->second] == ca) {
			paint(it->first, cb, ca);
			col[it->second] = cb;
			break;
		}
}

int main() {
	ifstream fin("colorare2.in");
	ofstream fout("colorare2.out");
	fin >> n >> m >> k;
	for(int i = 1 ; i <= k ; ++ i) {
		fin >> a[i] >> b[i];
		g[a[i]].push_back(make_pair(b[i], i));
		g[b[i]].push_back(make_pair(a[i], i));
	}
	for(int i = 1 ; i <= k ; ++ i) {
		int ca = getcolor(a[i]), cb = getcolor(b[i]);
		if(ca > p || cb > p)
			++ p;
		paint(b[i], ca, cb);
		col[i] = ca;
	}
	fout << p << '\n';
	for(int i = 1 ; i <= k ; ++ i)
		fout << col[i] << '\n';
}
