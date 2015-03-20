#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 100005;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("510a.in", "r", stdin);
	freopen("510a.out", "w", stdout);
	#endif

	int n, m;
	cin >> n >> m;

	bool aux = false;
	for(int i = 1 ; i <= n ; ++ i) {
		if(i % 2 == 1) {
			for(int j = 1 ; j <= m ; ++ j)
				cout << "#";
		}
		else {
			aux = !aux;
			if(aux) {
				for(int j = 1 ; j < m ; ++ j)
					cout << ".";
				cout << "#";
			}
			else {
				cout << "#";
				for(int j = 2 ; j <= m ; ++ j)
					cout << ".";
			}
		}
		cout << "\n";
	}
}
