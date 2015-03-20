#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<int> a;
int c1, c2, n;

int main() {
	ifstream fin("sort.in");
	ofstream fout("sort.out");
	
	fin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		int x;
		fin >> x;
		a.push_back(x);
		c1 += (x == 1);
		c2 += (x == 2);
	}

	int t, ans = 0;
	for(int i = c1 ; i < n ; ++ i) {
		if(a[i] == 1) {
			for(int j = t = 0 ; j < c1 ; ++ j) {
				if(a[j] == 2) {
					t = j;
					break;
				}
				if(a[j] == 3)
					t = j;
			}
			swap(a[i], a[t]);
			++ ans;
		}
	}
	for(int i = c1 + c2 ; i < n ; ++ i)
		ans += (a[i] == 2);
	
	fout << ans << '\n';

	
	
}
