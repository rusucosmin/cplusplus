#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 2005;

int n, a[maxn], fr[maxn], ind[maxn];

struct classcomp {
	inline bool operator () (const int &i, const int &j) const {
		return a[i] < a[j];
	}
};

int main() {
	#ifndef ONLINE_JUDGE
	freopen("471b.in", "r", stdin);
	freopen("471b.out", "w", stdout);
	#endif

	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> a[i];
		++ fr[a[i]];
		ind[i] = i;
	}
	int cnt = 0;
	vector <int> what;
	vector <int> what2;
	for(int i = 1 ; i < maxn && cnt != 2 ; ++ i)
		if(fr[i] >= 2) {
			++ cnt;
			what.push_back(i);
			if(fr[i] >= 3)
				what2.push_back(i);
		}
	sort(ind + 1, ind + n + 1, classcomp());
	if(cnt != 2 && !what2.size()) {
		cout << "NO\n";
		return 0;
	}	
	cout << "YES\n";
	for(int i = 1 ; i <= n ; ++ i)
		cout << ind[i] << ' ';
	cout << '\n';
	if(what.size() >= 2) {
		for(int i = 1 ; i <= n ; ++ i)
			if(a[ind[i]] == what[0]) {
				swap(ind[i], ind[i + 1]);
				break;
			}
		for(int i = 1 ; i <= n ; ++ i)
			cout << ind[i] << ' ';
		cout << '\n';
		for(int i = 1; i  <= n ; ++ i)
			if(a[ind[i]] == what[1]) {
				swap(ind[i], ind[i + 1]);
				break;
			}
		for(int i = 1 ; i <= n;  ++ i)
			cout << ind[i] << ' ';
		return 0;
	}
	for(int i = 1 ; i <= n ; ++ i)
		if(a[ind[i]] == what2[0]) {
			swap(ind[i], ind[i + 2]);
			break;
		}
	for(int i = 1 ; i <= n ; ++ i)
		cout << ind[i] << ' ';
	cout << '\n';
	for(int i = 1 ; i <= n ; ++ i)
		if(a[ind[i]] == what2[0]) {
			swap(ind[i], ind[i + 1]);
			break;
		}
	for(int i = 1 ; i <= n ; ++ i)	
		cout << ind[i] << ' ';
}
