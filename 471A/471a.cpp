#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, a[10];

int main() {
	n = 6;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> a[i];
	sort(a + 1, a + n + 1);
	int interval = 1;
	vector <int> ints;
	for(int i = 1 ; i <= n ; ++ i) {
		while(a[i] == a[i + 1]) {
			++ interval;
			++ i;
		}
		ints.push_back(interval);
		interval = 1;
	}
	sort(ints.begin(), ints.end());
	if(ints.size() == 1) {
		cout << "Elephant\n";
		return 0;
	}
	if(ints.size() == 2) {
		if(ints.back() == 4)
			cout << "Elephant\n";
		else if(ints.back() > 4)
			cout << "Bear\n";
		else
			cout << "Alien\n";
		return 0;
	}
	if(ints.size() == 3) {
		if(ints.back() >= 4)
			cout << "Bear\n";
		else
			cout << "Alien\n";
		return 0;
	}
	cout << "Alien\n";
}
