#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

const int maxn = 100005;
const int sigma = 26;

unordered_map<long long, int> mymap[sigma];
int n, a[maxn];
string s;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("519d.in", "r", stdin);
	freopen("519d.out", "w", stdout);
	#endif
	for(int i = 0 ; i < 26 ; ++ i)
		cin >> a[i];
	cin >> s;
	long long sum = 0, ans = 0;
	for(int i = 0 ; i < s.size() ; ++ i) {
		ans += mymap[s[i] - 'a'][sum];
		sum += a[s[i] - 'a'];
		++ mymap[s[i] - 'a'][sum];
	}
	cout << ans << '\n';
}
