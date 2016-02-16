#include <iostream>

using namespace std;

int cnt = 0;

inline bool check(string s) {
	int zero = 0;
	for(int i = 0 ; i < s.size() ; ++ i) {
		if(s[i] != '0' && s[i] != '1')
			return false;
		if(s[i] == '0')
			++ zero;
	}
	if(s.size() - zero != 1)
		return false;
	cnt += zero;
	return true;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
	#endif
	int n;
	cin >> n;
	string s;
	string oaieneagra = "";
	bool hasone = false;
	for(int i = 0 ; i < n ; ++ i) {
		cin >> s;
		if(s == "0") {
			cout << "0\n";
			return 0;
		}
		if(s == "1") {
			hasone = true;
			continue;
		}
		if(!check(s))
			oaieneagra = s;
	}
	if(oaieneagra == "")
		oaieneagra = "1";
	cout << oaieneagra;
	for(int i = 0 ; i < cnt ; ++ i)
		cout << "0";
}
