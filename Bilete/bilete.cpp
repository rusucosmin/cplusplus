#include <fstream>
#include <iostream>
#include <map>
#include <set>

using namespace std;

ifstream fin("bilete.in");
ofstream fout("bilete.out");

int n, k;
int st[10];
int nr1, nr2;
int ans;
map<int, bool> used;
set <int> s1, s2;

inline void back(int p) {
	if(p == k + 1) {
		int n1 = 0;
		int n2 = 0;
		for(auto it :s1)
			n1 = n1 * 100 + it;
		for(auto it :s2)
			n2 = n2 * 100 + it;
		if(n1 < n2) {
			fout << nr1 << '\n';
			++ ans;
		}
		else if (n1 == n2 && !used[nr1]) {
			used[nr1] = 1;
			fout << nr1 << '\n';
			++ ans;
		}
		return;
	}
	for(int i = st[p - 1] + 1 ; i <= n * n ; ++ i) {
		st[p] = i;
		int x = (i - 1) / n + 1;
		int y = (i - 1) % n + 1;
		nr1 = nr1 * 100 + x * 10 + y;
		nr2 = nr2 * 100 + x * 10 + n - y + 1;
		s1.insert(10*x + y);
		s2.insert(10*x + n - y + 1);
		back(p + 1);
		s1.erase(10*x + y);
		s2.erase(10*x + n - y + 1);
		nr1 /= 100;
		nr2 /= 100;
	}
}

int main() {
	fin >> n >> k;
	back(1);
	cerr << ans << '\n';
	
}
