#include <iostream>
#include <fstream>

using namespace std;

const int maxn = 100005;

int n, m, aib[maxn];

inline int lsb(int x) {
	return x & (-x);
}

inline void update(int pos, int value) {
	for(int i = pos ; i <= n ; i += lsb(i))
		aib[i] += value;
}

inline int query(int pos) {
	int sum = 0;
	for(int i = pos ; i > 0 ; i -= lsb(i))
		sum += aib[i];
	return sum;
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
		int op, x, y;
		fin >> op >> x;
		if(op == 0) {
			fin >> y;
			update(x, y);
		}
		if(op == 1) {
			fin >> y;
			fout << query(y) - query(x - 1) << '\n';	
		}
		if(op == 2) {
			int st = 1, dr = n, ans = -1;
			while(st <= dr) {
				int mid = ((st + dr) >> 1);
				int aux = query(mid);
				if(aux == x) {
					ans = mid;
					dr = mid - 1;
					continue;
				}
				if(aux < x)
					st = mid + 1;
				else
					dr = mid - 1;
			}
			fout << ans << '\n';
		}
	}
}
