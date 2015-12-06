#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<int, int> fr;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("525a.in", "r", stdin);
	freopen("525a.out", "w", stdout);
	#endif
	int n;
	string s;
	cin >> n >> s;
	int ans = 0;
	for(int i = 0 ; i < s.size() ; ++ i) {
		if(i % 2 == 0) {
			++ fr[s[i] - 'a'];
		}
		else
			if(!fr[s[i] - 'A'])
				++ ans;
			else
				-- fr[s[i] - 'A'];
	}
	cout << ans << '\n';
}
