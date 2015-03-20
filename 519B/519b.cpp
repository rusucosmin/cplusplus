#include <iostream>
#include <vector>
#include <set>

using namespace std;

multiset<int> s1, s2;
int n;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("519b.in", "r", stdin);
	freopen("519b.out", "w", stdout);
	#endif
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		int x;
		cin >> x;
		s1.insert(x);
	}
	for(int i = 1 ; i < n ; ++ i) {
		int x;
		cin >> x;
		s1.erase(s1.find(x));
		s2.insert(x);
	}
	cout << *s1.begin() << '\n';
	for(int i = 1 ; i < n - 1 ; ++ i) {
		int x;
		cin >> x;
		s2.erase(s2.find(x));
	}
	cout << *s2.begin() << '\n';
		
}

