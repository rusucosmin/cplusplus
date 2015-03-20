#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 100005;

int n;
pair<int, int> a[maxn];

struct classcomp {
	inline bool operator () (const pair<int, int> &a, const pair<int, int> &b) const {
		return a.first < b.first || (a.first == b.first && a.second < b.second);
	}
};

int main() {
	#ifndef ONLINE_JUDGE
	freopen("479c.in", "r", stdin);
	freopen("479c.out", "w", stdout);
	#endif

	cin >> n;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> a[i].first >> a[i].second;
	sort(a + 1, a + n + 1, classcomp());	
	int last = a[1].second;
	for(int i = 2 ; i <= n ; ++ i)
		if(last <= a[i].second)
			last = a[i].second;
		else
			last = a[i].first;
	cout << last << '\n';
}
