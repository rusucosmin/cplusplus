#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

char keyboard[] = "qwertyuiopasdfghjkl;zxcvbnm,./";

int main() {
	char s, mess[105];
	cin >> s >> mess;
	for(int i = 0 ; mess[i] ; ++ i) {
		int pos = strchr(keyboard, mess[i]) - keyboard;
		if(s == 'L')
			cout << keyboard[pos + 1];
		else
			cout << keyboard[pos - 1];
	}
	
}
