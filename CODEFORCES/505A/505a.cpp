#include <fstream>
#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

const int maxn = 10005;

char s[maxn];

int main() {
	string s;
	cin >> s;
	for(int i = 0 ; i <= s.size() ; ++ i) {
		for(char x = 'a' ; x <= 'z' ; ++ x) {
			s.insert(i, 1, x);
			string aux = s;
			reverse(aux.begin(), aux.end());
			if(aux == s) {
				cout << aux << '\n';
				return 0;
			}
			s.erase(i, 1);
		}
	}
	cout << "NA\n";
}
