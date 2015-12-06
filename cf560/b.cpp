#include <iostream>

using namespace std;

inline bool solve(int a1, int b1, int a2, int b2, int a3, int b3) {
	if(a2 + a3 <= a1 && max(b2, b3) <= b1)
		return 1;
	else
		if(a2 + b3 <= a1 && max(a3, b2) <= b1) 
			return 1;
		else
			if(b2 + a3 <= a1 && max(b3, a2) <= b1)
				return 1;
			else
				if(b2 + b3 <= a1 && max(a2, a3) <= b1)
					return 1;
				else
					return 0;
}

int main() {
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	int a1, b1, a2, b2, a3, b3;
	cin >> a1 >> b1 >> a2 >> b2 >> a3 >> b3;
	if(solve(a1, b1, a2, b2, a3, b3) || solve(b1, a1, a2, b2, a3, b3))
		cout << "YES\n";
	else
		cout << "NO\n";
}
