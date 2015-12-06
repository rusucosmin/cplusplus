#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int t, n;
vector <int> v;

int main() {
	ifstream fin("codejamb.in");
	ofstream fout("codejamb.out");
	fin >> t;
	for(int test = 1 ; test <= t ; ++ test) {
		fin >> n;
		int maxvalue = 0;
		for(int i = 1 ; i <= n ; ++ i) {
			int x;
			fin >> x;
			v.push_back(x);
			maxvalue = max(maxvalue, x);
		}
		int ans = maxvalue;
		for(int i = 1 ; i <= maxvalue ; ++ i) {
			int act = 0;
			for(int j = 0 ; j < n ; ++ j) {
				int times = v[j] / i;	
				int rest = v[j] % i;
				if(rest)
					++ times;
				act = act + times - 1;
			}
			act += i;
			ans = min(ans, act);
		}
		fout << "Case #" << test << ": " << ans << '\n';
		v.clear();
	}
}
