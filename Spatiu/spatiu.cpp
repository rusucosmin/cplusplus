#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream fin("spatiu.in");
	ofstream fout("spatiu.out");
	int t;
	fin >> t;
	while(t -- ) {
		int n = 1, m = 1;
		int lg;
		string s;
		fin >> lg >> s;
		for(int i = 0 ; i < lg ; ++ i) {
			if(s[i] == '1' || s[i] == '2' || s[i] == '5')
				++ n;
			if(s[i] == '3' || s[i] == '4' || s[i] == '5')
				++ m;
		}
		fout << 1LL * n * m << '\n';
	}
}
