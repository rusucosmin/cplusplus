#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <stdio.h>

using namespace std;

inline int dist(pair<int, int> x, pair<int, int> y) {
	return (x.first - y.first) * (x.first - y.first) + (x.second - y.second) * (x.second - y.second);
}

int main() {
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
	
	int t;
	cin >> t;
	for(int test = 1 ; test <= t ; ++ test) {
		vector <pair<int, int> > p;
		int n;
		cin >> n;
		for(int i = 0 ; i < n ; ++ i) {
			int x, y;
			cin >> x >> y;
			p.push_back(make_pair(x, y));
		}
		long long cnt = 0;
		for(int i = 0 ; i < n ; ++ i) {
			unordered_map<int, int> freq;
			for(int j = 0 ; j < n; ++ j)
				if(i != j)
					++ freq[dist(p[i], p[j])];
			for(auto it : freq)
				cnt += ((1LL * it.second * (it.second - 1)) / 2);
		}
		cout << "Case " << "#" << test << ": " << cnt << '\n';
	}
}
