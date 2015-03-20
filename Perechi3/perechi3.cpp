#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;


int main() {
	ifstream fin("perechi3.in");
	ofstream fout("perechi3.out");
	long long t, n, rad;
	fin >> t;
	while(t --) {
		fin >> n;
		long long ans = 0;
		rad = sqrt((double)n);
		for(int i = 1 ; i <= rad ; ++ i)
			ans  += (n / i);
		ans = ans * 2LL - 1LL*rad*rad;
		fout << ans << '\n';
	}
	
}
