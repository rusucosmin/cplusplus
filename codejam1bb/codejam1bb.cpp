#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;

map<pair<int, int>, int> _hash;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = { 0,-1, 0, 1};

int test, n, r, c;

inline pair<int, int> getcoord(int number) {
	return make_pair(number / c, number % c);
}

inline bool inside(pair<int, int> x) {
	return x.first >= 0 && x.first < r && x.second >= 0 && x.second < c;
}

int main() {
	freopen("codejam1bb.in", "r", stdin);
	freopen("codejam1bb.out", "w", stdout);
	
	cin >> test;
	for(int t = 1 ; t <= test ; ++ t) {
		cin >> r >> c >> n;
		int nodes = r * c;
		int maxconf = (1 << nodes);
		int ans = 0x3f3f3f3f;
		for(int conf = 0 ; conf < maxconf ; ++ conf) {
			if(__builtin_popcount(conf) != n)
				continue;
			int happ = 0;
			for(int node = 0 ; node < nodes ; ++ node) {
				if(conf & (1 << node)) {
					pair<int, int> coord = getcoord(node);
					for(int d = 0 ; d < 2 ; ++ d) {
						pair<int, int> act = make_pair(coord.first + dx[d], coord.second + dy[d]);
						if(!inside(act))
							continue;
						int newnode = act.first * c + act.second;
						if(conf & (1 << newnode))
							++ happ;
					}
				}
			}
			ans = min(ans, happ);
		}
		cout << "Case #" << t << ": " << ans << '\n';
	}
}
