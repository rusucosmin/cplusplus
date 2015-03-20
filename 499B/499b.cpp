#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <map>

using namespace std;

map<int, string> lower;
map<string, int> ind;
int n, m;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("499b.in", "r", stdin);
	#endif
	cin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		string a, b;
		cin >> a >> b;
		ind[a] = ind[b] = i;
		if(a.size() <= b.size())
			lower[i] = a;
		else
			lower[i] = b;
	}
	for(int i = 1 ; i <= n ; ++ i) {
		string s;
		cin >> s;
		cout << lower[ind[s]] << ' ';
	}
}
