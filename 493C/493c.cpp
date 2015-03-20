#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector <pair<int, int> > v;

inline int getscore(int two, int three) {
	return two * 2 + three * 3;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("493c.in", "r", stdin);
	freopen("493c.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		int x;
		cin >> x;
		v.push_back(make_pair(x, 1));
	}
	cin >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		int x;
		cin >> x;
		v.push_back(make_pair(x, 2));
	}
	v.push_back(make_pair(0, 0));
	sort(v.begin(), v.end());

	int less1 = 0, less2 = 0;
	int ans = -0x3f3f3f3f, score1 = 0, score2 = 0;
	for(int i = 0 ; i < v.size() ; ++ i) {
		int first = i;
		if(v[i].second == 1)
			++ less1;
		if(v[i].second == 2)
			++ less2;
		while(i + 1 < v.size() && v[i].first == v[i + 1].first) {
			++ i;
			if(v[i].second == 1)
				++ less1;
			if(v[i].second == 2)
				++ less2;
		}

//		cerr << v[i].first << ' ' << less1 << ' ' << less2 << ' ';

		int actscore1 = getscore(less1, n - less1);
		int actscore2 = getscore(less2, m - less2);

//		cerr << actscore1 << ' ' << actscore2 << '\n';

		if(ans < actscore1 - actscore2) {
			ans = actscore1 - actscore2;
			score1 = actscore1;
			score2 = actscore2;
		}
	}
	cout << score1 << ':' << score2 << '\n';
}

