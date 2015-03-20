#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

using namespace std;

const int maxn = 2000005;

char a[maxn], b[maxn];
int n, pi[maxn], m;
vector <int> matches;

int main() {
	ifstream fin("strmatch.in");
	ofstream fout("strmatch.out");

	fin >> a + 1 >> b + 1;
	n = strlen(a + 1);
	m = strlen(b + 1);

	int k = 0;
	for(int i = 2 ; i <= n ; ++ i) {
		while(k > 0 && a[k + 1] != a[i])
			k = pi[k];
		if(a[k + 1] == a[i])
			++ k;
		pi[i] =  k;
	}
	k = 0;
	for(int i = 1 ; i <= m ; ++ i) {
		while(k > 0 && a[k + 1] != b[i])
			k = pi[k];
		if(a[k + 1] == b[i])
			++ k;
		if(k == n)
			matches.push_back(i - n);
	}
	fout << matches.size() << '\n';
	for(int i = 0 ; i < min(1000, int(matches.size())) ; ++ i)
		fout << matches[i] << ' ';
}
