#include <fstream>
#include <iostream>

using namespace std;

ifstream fin("taste.in");
ofstream fout("taste.out");

const int maxi = 60;

int main() {


	long long x, y;

	fin >> x >> y;

	long long sol = 1LL << maxi;
	long long sol1 = 1;
	long long sol2 = maxi;

	for(long long i = 0 ; i <= maxi ; ++ i) {
		long long ip = (1LL << i);
		long long st = 0, dr = (1LL << maxi) / ip + 10;
		while(st <= dr) {
			long long mid = ((st - dr) >> 1LL) + dr;
			if(mid * ip < x)
				st = mid + 1;
			else
				if(mid * ip > y)
					dr = mid - 1;
				else
					if(mid * ip >= x && mid * ip <= y) {
						if(sol > mid + i) {
							sol = mid + i;
							sol1 = mid;
							sol2 = i;
						}
						dr = mid - 1;
					}
		}

	}
	fout << sol1 << ' ' << sol2 << '\n';
}
