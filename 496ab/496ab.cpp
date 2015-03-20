#include <iostream>
#include <deque>
#include <string>

using namespace std;

const int maxn = 1005;

deque <char> dq;
string ans;
int n;

inline string solve(int d) {
	string ret = "";
	deque <char> dek = dq;
	for(int i = 1 ; i <= n ; ++ i) {
		string s = "";
		deque <char> aux;
		aux = dek;
		while(!aux.empty()) {
			s = s + (char)((aux.front() - '0' + d) % 10 + '0');
			aux.pop_front();
		}
		if(ret == "")
			ret = s;
		else if(ret > s)
			ret = s;
		char ba = dek.back();
		dek.pop_back();
		dek.push_front(ba);
	}
	return ret;
}

int main() {
	cin >> n;
	for(int i = 0 ; i < n ; ++ i) {
		char s;
		cin >> s;
		dq.push_back(s);
	}
	string ans = "";
	for(int i = 0 ; i < 10 ;  ++ i) {
		string act = solve(i);
		if(ans == "")
			ans = act;
		else if(ans > act)
			ans = act;
	}
	cout << ans << '\n';
}
