#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int n, ans;
string s, t;
unordered_map<string, int> mymap1;
unordered_map<char, int> mymap2, mymap3;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("527b.in", "r", stdin);
	freopen("527b.out", "w", stdout);
	#endif
	cin >> n;
	cin >> s;
	cin >> t;
	for(int i = 0 ; i < n ; ++ i) {
		if(s[i] == t[i])
			continue;
		++ ans;
		string aux = "";
		aux += s[i];
		aux += t[i];
		mymap1[aux] = i + 1;
		mymap2[s[i]] = i + 1;
		mymap3[t[i]] = i + 1;
	}
	for(int i = 0 ; i < n;  ++ i) {
		if(s[i] == t[i])
			continue;
		string aux = "";
		aux += t[i];
		aux += s[i];
		if(mymap1.find(aux) != mymap1.end()) {
			cout << ans - 2 << '\n' << mymap1[aux] << ' ' << i + 1 << '\n';
			return 0;
		}
	}
	for(int i = 0 ; i < n ; ++ i) {
		if(s[i] == t[i])
			continue;
		if(mymap2.find(t[i]) != mymap2.end()) {
			cout << ans - 1 << '\n' << i + 1 << ' ' << mymap2[t[i]] << '\n';
			return 0;
		}
		if(mymap3.find(s[i]) != mymap3.end()) {
			cout << ans - 1 << '\n' << i + 1 << ' ' << mymap3[s[i]] << '\n';
			return 0;
		}
	}
	cout << ans << '\n' << -1 << ' ' << -1 << '\n';
}
