#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 1005;

int n;
double x[maxn], y[maxn];

inline double getslope(int i, int j) {
	if(x[i] == x[j])
		return -100000003;
	return (y[j] - y[i]) / (x[j] - x[i]);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("514b.in", "r", stdin);
	freopen("514b.out", "w", stdout);
	#endif

	cin >> n >> x[0] >> y[0];
	vector <double> slopes;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> x[i] >> y[i];
		slopes.push_back(getslope(0, i));
	}
	sort(slopes.begin(), slopes.end());
	slopes.resize(unique(slopes.begin(), slopes.end()) - slopes.begin());
	cout << slopes.size() << '\n';	
}
