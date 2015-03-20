#include <fstream>
#include <math.h>
#include <iomanip>

using namespace std;

ifstream fin("spider-man.in");
ofstream fout("spider-man.out");

int main() {
	double xc, yc, r, x1, y1, x2, y2;

	fin >> xc >> yc >> r >> x1 >> y1 >> x2 >> y2;

	double xm = (x1 + x2) / 2.0;
	double ym = (y1 + y2) / 2.0;

	double cat1 = r - sqrt( (xm - xc) * (xm - xc) + (ym - yc) * (ym - yc) );

	fout << fixed << setprecision(6) << 2.0 * (cat1 * cat1 + (x1 - xm) * (x1 - xm) + (y1 - ym) * (y1 - ym)) << '\n';
}
