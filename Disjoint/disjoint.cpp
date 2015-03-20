#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 100005;

int n, m, father[maxn];

inline int find(int x) {
	if(x != father[x])
		father[x] = find(father[x]);
	return father[x];
}

inline void unite(int x, int y) {
	father[x] = y;	
}

int main() {
	ifstream fin("disjoint.in");
	ofstream fout("disjoint.out");
	fin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i)
		father[i] = i;
	for(int i = 1 ; i <= m ; ++ i) {
		int op, x, y;
		fin >> op >> x >> y;
		if(op == 1)
			unite(find(x), find(y));
		else
			if(find(x) == find(y))
				fout << "DA\n";
			else
				fout << "NU\n";
	}
}
