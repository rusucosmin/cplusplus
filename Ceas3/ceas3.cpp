#include <fstream>
#include <math.h>
#include <iomanip>

using namespace std;

int degree;

int main() {
	ifstream fin("ceas3.in");
	ofstream fout("ceas3.out");

	while (fin >> degree) {
		int addH = degree / 30;
		degree %= 30;
		int H = (9 + addH ) % 12;
		int addM = degree * 2;
		out << setw(2) << setfill('0') << H << ':';
		fout << setw(2) << setfill('0') << addM << '\n';
	}
}
