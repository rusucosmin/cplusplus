#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ifstream fin("produs4.in");
	ofstream fout("produs4.out");
	int t;
	fin >> t;
	while(t -- ) {
		int n; vector <int> v;
		fin >> n;
		for(int i = 0 ; i < n ; ++ i) {
			int x;
			fin >> x;
			v.push_back(x);
		}
		sort(v.begin(), v.end(), greater<int>());
		long long ans = max(1LL * v[0] * v[1] * v[2], 1LL * v[0] * v[v.size() - 2] * v[v.size() - 1]);
		fout << ans << '\n';
	}
}
