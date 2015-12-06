#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector <int> getMatches(string s, string t) {
	int n = s.size();
	int m = t.size();
	vector <int> pi(n);
	int k = -1;
	pi[0] = -1;
	for(int i = 1 ; i < n ; ++ i) {
		while(k != -1 && s[k + 1] != s[i])
			k = pi[k];
		if(s[k + 1] == s[i])
			++ k;
		pi[i] = k;
	}
	k = -1;
	vector <int> v;
	for(int i = 0 ; i < m ; ++ i) {
		while(k != -1 && s[k + 1] != t[i])
			k = pi[k];
		if(s[k + 1] == t[i])
			++ k;
		if(k == n - 1) {
			v.push_back(i - k);	
		}
	}
	return v;
}

int main() {
	ifstream fin("strmatch.in");
	ofstream fout("strmatch.out");

	string s, t;
	getline(fin, s);
	getline(fin, t);
	vector <int> matches = getMatches(s, t);
	fout << matches.size() << '\n';
	for(int i = 0 ; i < min(1000, int(matches.size())) ; ++ i)
		fout << matches[i] << ' ';
}
