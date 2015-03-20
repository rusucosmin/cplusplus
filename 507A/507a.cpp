#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



int main() {
	#ifndef ONLINE_JUDGE
	freopen("507a.in", "r", stdin);
	freopen("507a.out", "w", stdout);
	#endif

	int n, k;
	vector <pair<int, int> > v;

	cin >> n >> k;
	for(int i = 1 ; i <= n ; ++ i) {
		int x;
		cin >> x;
		v.push_back(make_pair(x, i));
	}
	sort(v.begin(), v.end());

	vector <int> vans;

	int days = 0, ans = 0;
	for(int i = 0 ; i < n ; ++ i) {
		if(days + v[i].first <= k) {
			days += v[i].first;
			++ ans;
			vans.push_back(v[i].second);
		}
		else
			break;
	}
	cout << ans << '\n';
	for(auto it : vans)
		cout << it << ' ';

	
}
