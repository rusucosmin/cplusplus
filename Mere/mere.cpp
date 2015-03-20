#include <fstream>

using namespace std;

int main() {
	ifstream fin("mere.in");
	ofstream fout("mere.out");

	int t;
	fin >> t;
	while (t --) {
		int n, k;
		fin >> n >> k;
		int r = n % k;
		int p = n / k;
		if(n < k)
			fout << "Remiza\n";
		else
			if(p % 2 == 1)
				fout << "Santa Klaus\n";
			else
				if(r == 0)
					fout << "Remiza\n";
				else
					fout << "Santa Klaus\n";
	}
}
