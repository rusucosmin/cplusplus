#include <iostream>
#include <string.h>

using namespace std;

const int maxn = 200005;

char a[maxn], b[maxn];
int n;

inline bool check(int x1, int x2, int y1, int y2) {
	for(int i = x1, j = y1 ; i <= x2 && j <= y2 ; ++ i, ++ j)
		if(a[i] != b[j])
			return 0;
	return 1;
}


inline bool dei(int st1, int dr1, int st2, int dr2) {
	if(dr1 - st1 + 1 != dr2 - st2 + 1)
		return 0;
	int lg = dr1 - st1 + 1;
	if(lg % 2 == 1)
		return check(st1, dr1, st2, dr2);
	bool ok = check(st1, dr1, st2, dr2);
	if(ok)
		return 1;
	else {
		int mij1 = (st1 + dr1) / 2;
		int mij2 = (st2 + dr2) / 2;
		return (dei(st1, mij1, st2, mij2) && dei(mij1 + 1, dr1, mij2 + 1, dr2))
			|| (dei(mij1 + 1, dr1, st2, mij2) && dei(st1, mij1, mij2 + 1, dr2));
	}
}

int main() {
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	cin.getline(a, maxn);
	cin.getline(b, maxn);
	n = strlen(a);
	if(n % 2 == 1) {
		if(strcmp(a, b) == 0)
			cout << "YES\n";
		else
			cout << "NO\n";
		return 0;
	}
	if(dei(0, n - 1, 0, n - 1))
		cout << "YES\n";
	else
		cout << "NO\n";
}
