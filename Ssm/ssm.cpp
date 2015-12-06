#include <iostream>
#include <fstream>

using namespace std;

const int oo = 0x3f3f3f3f;

int main() {
	ifstream fin("ssm.in");
	ofstream fout("ssm.out");
	int n, x, bestsum = -oo, sum = -oo, start, beg, end;
	fin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		fin >> x;
		if(sum >= 0)
			sum += x;
		else {
			sum = x;
			start = i;
		}
		if(sum > bestsum) {
			bestsum = sum;	
			beg = start;
			end = i;
		}
	}
	fout << bestsum << ' ' << beg << ' ' << end << '\n';
}
