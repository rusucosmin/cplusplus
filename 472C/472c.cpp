#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 100005;

int n, ind[maxn];
pair<string, string> aux[maxn];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("472c.in", "r", stdin);
	freopen("472c.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> aux[i].first >> aux[i].second;
		if(aux[i].first > aux[i].second)
			swap(aux[i].first, aux[i].second);
	}
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> ind[i];
	}
	string last = aux[ind[1]].first;
	for(int i = 2 ; i <= n ; ++ i) {
		if(aux[ind[i]].first >= last)
			last = aux[ind[i]].first;
		else if(aux[ind[i]].second >= last)
			last = aux[ind[i]].second;
		else {
			cout << "NO\n";
			return 0;
		}
	}
	cout << "YES\n";
}
