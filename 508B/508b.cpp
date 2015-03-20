#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

const int maxn = 100005;

char s[maxn];
int n;

int main() {
	cin.getline(s + 1, maxn);
	n = strlen(s + 1);
	bool haseven = 0;
	for(int i = 1 ; i <= n ; ++ i)
		if((s[i] - '0') % 2 == 0)
			haseven = 1;
	if(!haseven) {
		cout << "-1\n";
		return 0;
	}
	for(int i = 1 ; i < n ; ++ i)
		if((s[i] - '0') % 2 == 0 && s[i] <= s[n]) {
			swap(s[i], s[n]);
			cout << s + 1 << '\n';
			return 0;
		}
	for(int i = n - 1 ; i >= 1 ; -- i)
		if((s[i] - '0') % 2 == 0 && s[i] >= s[n]) {
			swap(s[i], s[n]);
			cout << s + 1 << '\n';
			return 0;
		}
	
	
	
}
