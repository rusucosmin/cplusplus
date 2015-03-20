#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const int mod = 666013;

vector <int> g[mod];
int n;

inline bool find(int x) {
	for(vector <int> :: iterator it = g[x%mod].begin() ; it != g[x%mod].end() ; ++ it)
		if(*it == x)
			return true;
	return false;
}

inline void insert(int x) {
	if(find(x))
		return ;
	g[x % mod].push_back(x);
}

inline void erase(int x) {
	if(!find(x))
		return ;
	for(vector <int> :: iterator it = g[x%mod].begin() ; it != g[x%mod].end() ; ++ it)
		if(*it == x) {
			 g[x%mod].erase(it);
			 return ;
		}

}

int main() {
	ifstream fin("hashuri.in");
	ofstream fout("hashuri.out");

	fin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		int op, x;
		fin >> op >> x;
		if(op == 1)
			insert(x);
		if(op == 2)
			erase(x);
		if(op == 3)
			fout << find(x) << '\n';
	}
}
