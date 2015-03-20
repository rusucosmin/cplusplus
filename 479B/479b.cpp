#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const int maxn  = 105;

vector <pair<int, int> > sol;
int n, k, a[maxn];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("479b.in", "r", stdin);
	freopen("479b.out", "w", stdout);
	#endif
	cin >> n >> k;
	for(int i = 1 ; i <= n ; ++ i)	
		cin >> a[i];
	int pmin = 1, pmax = 1;
	for(int i = 1 ; i <= k ; ++ i) {
		pmin = 1; pmax = 1;
		for(int j = 1 ; j <= n ; ++ j) {
			if(a[pmin] > a[j])
				pmin = j;
			if(a[pmax] < a[j])
				pmax = j;
		}
		if(pmin == pmax)
			break;
		-- a[pmax];
		++ a[pmin];
		sol.push_back(make_pair(pmax, pmin));
	}
	pmin = pmax = 1;
	for(int i = 1 ; i <= n ; ++ i) {
		if(a[pmin] > a[i])
			pmin = i;
		if(a[pmax] < a[i])
			pmax = i;
	}
	cout << a[pmax] - a[pmin]  << ' ' << sol.size() << '\n';
	for(auto it : sol)
		cout << it.first << ' ' << it.second << '\n';
}
