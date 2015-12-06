#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int n, t;
string s1, s2;

inline char next(char s) {
	return (char)((s - 'a' + 1) % 26 + 'a');
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
	#endif
	cin >> n >> t;
	cin >> s1 >> s2;
	string x = "";
	vector <int> ind;
	int equals = n - t;
	for(int i = 0 ; i < n ; ++ i)
		if(s1[i] != s2[i]) {
			ind.push_back(i);
			char nxt = next(s1[i]);
			if(nxt == s2[i])
				nxt = next(nxt);
			x = x + nxt;
		}
		else {
			if(equals == 0) {
				char nxt = next(s1[i]);
				if(nxt == s2[i])
					nxt = next(nxt);
				x = x + nxt;
			}
			else {
				x = x + s1[i];
				-- equals;
			}
		}
	/// am ramas cu equals elemente in care s1 si s2 trebuie sa fie egale;
	if(2 * equals > ind.size()) {
		cout << "-1\n";
		return 0;
	}
	int i = 0;
	for( ; i < equals ; ++ i)
		x[ind[i]] = s1[ind[i]];
	int j = 0;
	for( ; j < equals ; ++ j, ++ i)
		x[ind[i]] = s2[ind[i]];
	cout << x << '\n';
}
