#include <fstream>

using namespace std;

int n, t;
long long pow2[1000], k;

int main() {
	ifstream fin("semipal.in");
	ofstream fout("semipal.out");

	fin >> t;
	pow2[0] = 1;
	for(int i = 1 ; i <= 63 ; ++ i)
		pow2[i] = 2LL * pow2[i - 1];
	while(t -- ) {
		fin >> n >> k;
		-- n ; --n;
		if(n == 0) {
			if(k == 1)
				fout << "aa\n";
			else
				fout << "bb\n";
			continue;
		}
		if(k <= pow2[n]) {
			fout << "a";
			for(int i = n - 1 ; i >= 0 ; -- i) {
				if(k <= pow2[i])
					fout << "a";
				else {
					fout << "b";
					k -= pow2[i];
				}
			}
			fout << "a";
		}
		else {
			k -= pow2[n];
			fout << "b";
			for(int i = n - 1 ; i >= 0 ; -- i) {
				if(k <= pow2[i])
					fout << "a";
				else {
					fout << "b";
					k -= pow2[i];
				}
			}
			fout << "b";
		}
		fout << '\n';
	}
	
}
