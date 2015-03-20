#include <iostream>
#include <fstream>

using namespace std;

const int maxn = 100005;

int n, m, aib[maxn];

inline int lsb(int x) {
	return x & (-x);
}

inline void update(int node, int value) {
	for(int i = node ; i <= n ; i += lsb(i))
		aib[i] += value;
}

inline int query(int node) {
	int sum = 0;
	for(int i = node ; i > 0 ; i -= lsb(i))
		sum += aib[i];
	return sum;
}

inline int binarysearch(int x) {
	int st = 1, dr = n, ans = -1;
	while(st <= dr) {
		int mid = ((st + dr) >> 1);
		int q = query(mid);
		if(q == x) {
			ans = mid;
			dr = mid - 1;
		}
		if(q > x)
			dr = mid - 1;
		else
			st = mid + 1;
	}
	return ans;
}

int main() {
	ifstream fin("aib.in");
	ofstream fout("aib.out");

	fin >> n >> m;
	for(int i = 1 ; i <= n ; ++ i) {
		int x;
		fin >> x;
		update(i, x);
	}
	for(int i = 1 ; i <= m ; ++ i) {
		int op;
		fin >> op;	
		++ op;
		if(op == 1) {
			int x, y;
			fin >> x >> y;
			update(x, y);
		}
		if(op == 2) {
			int x, y;
			fin >> x >> y;
			fout << query(y) - query(x - 1) << '\n';
		}
		if(op == 3) {
			int x;
			fin >> x;
			fout << binarysearch(x) << '\n';
		}
	}
}
