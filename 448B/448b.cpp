#include <iostream>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

string s, t;
map<char, int> mymap, mymap2;

int main() {
	cin >> s >> t;
	if(s.size() < t.size()) {
		cout << "need tree\n";
		return 0;
	}
	bool first = false, second = false;
	if(s.size() > t.size())
		first = true;	
	int j = 0, i = 0;;
	for(i = 0 ; i < t.size() ; ++ i) {
		while(j < s.size() && t[i] != s[j])
			++ j;
		if(j >= s.size())
			break;
		++ j;
	}
	int ans = 0;
	if(i != t.size())
		second = true;
	for(int i = 0 ; i < t.size() ; ++ i)
		++ mymap[t[i]];
	for(int i = 0 ; i < s.size() ; ++ i)
		++ mymap2[s[i]];
	bool okay = true;
	for(int i = 0 ; i < t.size() ; ++ i) {
		if(mymap2[t[i]] < mymap[t[i]])
			okay = false;	
		if(mymap2[t[i]] > mymap[t[i]])
			first = true;
	}
	if(!okay) {
		cout << "need tree\n";
		return 0;
	}
	if(first) {
		// need automaton
		if(second)
			cout << "both\n";
		else
			cout << "automaton\n";
	}
	else {
		if(second)
			cout << "array\n";
		else
			cout << "needtree\n";
	}
}
