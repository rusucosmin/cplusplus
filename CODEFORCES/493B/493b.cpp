#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

vector <int> points[2];
int n, lastx;
long long sum[2];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("493b.in", "r", stdin);
	#endif
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		int x;
		cin >> x;
		points[x < 0].push_back(x < 0 ? -x : x);
		sum[x < 0] += (x < 0) ? -x : x;
		lastx = x;
	}
	if(sum[0] > sum[1]) {
		cout << "first\n";
		return 0;
	}
	if(sum[0] < sum[1]) {
		cout << "second\n";
		return 0;
	}
	for(int i = 0 ; i < min(points[0].size(), points[1].size()) ; ++ i) {
		if(points[0][i] > points[1][i]) {
			cout << "first\n";
			return 0;
		}
		if(points[0][i] < points[1][i]) {
			cout << "second\n";
			return 0;
		}
	}
	if(points[0].size() == points[1].size()) {
		if(lastx > 0)
			cout << "first\n";
		else
			cout << "second\n";
		return 0;
	}
	if(points[0].size() > points[1].size())
		cout << "first\n";
	else
		cout << "second\n";
	return 0;
}
