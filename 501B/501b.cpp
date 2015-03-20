#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

map<string, int> idx;
map<int, string> aux, last;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("501b.in", "r", stdin);
	freopen("501b.out", "w", stdout);
	#endif
	int n;
	cin >> n;
	int users = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		string a, b;
		cin >> a >> b;
		if(!idx[a]) {
			idx[a] = ++ users;
			aux[users] = a;
		}
		last[idx[a]] = b;
		idx[b] = idx[a];
	}
	cout << users << '\n';
	for(int i = 1 ; i <= users ; ++ i) {
		cout << aux[i] << ' ' << last[i] << '\n';
	}

}
