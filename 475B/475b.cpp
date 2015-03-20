#include <iostream>
#include <fstream>

using namespace std;

int n, m;
string s1, s2;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("475b.in", "r", stdin);
	freopen("475b.out", "w", stdout);
	#endif
	cin >> n >> m;
	cin >> s1 >> s2;
	string corners = ""; corners += s1.front(); corners += s2.front(); corners += s1.back(); corners += s2.back();
	if(corners == "<v>^" || corners == ">^<v")
		cout << "YES\n";
	else
		cout << "NO\n";
}
