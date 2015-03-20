#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

struct classcomp {
	inline bool operator () (const pair<int, int> &a, const pair<int, int> &b) const {
		return a.second < b.second;
	}
};

int main() {
	#ifndef ONLINE_JUDGE
	freopen("528b.in", "r", stdin);
	freopen("528b.out", "w", stdout);
	#endif
	int n;
	vector <pair<int, int> > v;
	cin >> n;
	for(int i = 0 ; i < n;  ++ i) {
		int x, y;
		cin >> x >> y;
		v.push_back(make_pair(x - y, x + y));
	}
	sort(v.begin(), v.end(), classcomp());
	int ans = 1;
	int aux = v[0].second;
	for(int i = 1 ; i < n ; ++ i)
		if(aux <= v[i].first) {
			++ ans;
			aux = v[i].second;
		}
	cout << ans << '\n';
}
