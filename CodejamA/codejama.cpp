#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream fin("codejama.in");
	ofstream fout("codejama.out");

	int t;
	fin >> t;
	for(int test = 1 ; test <= t ; ++ test) {
		int smax;
		string s;
		fin >> smax;
		fin >> s;
		int needed = 0, standing = s[0] - '0';
		for(int i = 1 ; i <= smax ; ++ i) {
			if(s[i] == '0')
				continue;
			if(standing < i) {
				needed += (i - standing);
				standing += (i - standing);
			}
			standing += (s[i] - '0');
		}
		fout << "Case #" << test << ": " << needed << '\n';
	}
	
}
