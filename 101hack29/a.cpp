#include <iostream>

using namespace std;

int cnt[2], diff[2];

int main() {
	#ifdef HOME
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
	#endif
	string a, b;
	cin >> a >> b;
	if(a.size() != b.size()) {
		cout << "-1\n";
		return 0;
	}
	for(int i = 0 ; i < a.size() ; ++ i)
		if(a[i] != b[i])
			++ cnt[a[i] - '0'];
	if(cnt[1] != cnt[0])
		cout << "-1\n";
	else
		cout << cnt[0] << '\n';
}
