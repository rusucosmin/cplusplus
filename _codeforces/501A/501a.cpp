#include <iostream>
using namespace std;

inline int cost(int p, int t) {
	return max((3 * p / 10), (p - (p * t) / 250));
}

int main() {
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	if(cost(a, c) > cost(b, d))
		cout << "Misha\n";
	else
		if(cost(a, c) == cost(b, d))
			cout << "Tie\n";
		else
			cout << "Vasya\n";
}
