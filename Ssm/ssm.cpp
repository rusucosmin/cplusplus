#include <iostream>
#include <fstream>

using namespace std;

const int maxn = 6000005;

int n, actsum, st, dr, ind;
int ansst, ansdr, bestsum = -0x3f3f3f3f, sum;

int main() {
	ifstream fin("ssm.in");
	ofstream fout("ssm.out");

	fin >> n;
	sum = -0x3f3f3f3f;
	for(int i = 1 ; i <= n ; ++ i) {
		int x;
		fin >> x;
		if(sum < 0) {
			sum = x;
			st = i;
		}
		else
			sum += x;
		if(bestsum < sum) {
			bestsum = sum;
			ansst = st;
			ansdr = i;
		}
	}
	fout << bestsum << ' ' << ansst << ' ' << ansdr << '\n';
}
