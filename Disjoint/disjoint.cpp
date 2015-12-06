#include <iostream>
#include <fstream>

using namespace std;

const int maxn = 100005;

int n, m, father[maxn], sz[maxn];

inline int find(int x) {
	while(x != father[x])
		x = father[x];
	return x;
}

inline void unite(int x, int y) {
	int tx = find(x);
	int ty = find(y);
	if(tx == ty)
		return ;
	if(sz[tx] == sz[ty])
		++ sz[tx];
	if(sz[tx] > sz[ty])
		father[ty] = tx;
	else
		father[tx] = ty;
}	

inline int Find(int x) {
	if(father[x] != x)
		father[x] = Find(father[x]);
	return father[x];
}

inline void Unite(int x, int y) {
	father[Find(x)] = Find(y);
}

int main() {
	ifstream fin("disjoint.in");
	ofstream fout("disjoint.out");

	fin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i) {
		father[i] = i;
		sz[i] = 1;
	}
	for(int i = 1 ; i <= m ; ++ i) {
		int op, x, y;
		fin  >> op >> x >> y;
		if(op == 1)
			Unite(x, y);
		else
			if(Find(x) == Find(y))
				fout << "DA\n";
			else
				fout << "NU\n";
	}
	
}
