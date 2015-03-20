#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int n;
vector <int> g[3];

int main() {
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		int x;
		cin >> x;
		g[x - 1].push_back(i);
	}

	cout << min(g[0].size(), min(g[1].size(), g[2].size())) << '\n';
	for(int i = 0 ; i < min(g[0].size(), min(g[1].size(), g[2].size())) ; ++ i)
		cout << g[0][i] << ' ' << g[1][i] << ' ' << g[2][i] << '\n';
	
}
