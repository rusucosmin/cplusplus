#include <fstream>
#include <math.h>
#include <iomanip>

using namespace std;

double a, b, xi, yi;
int T;

inline double dis(pair<double, double> x, pair<double, double> y) {
	return sqrt((x.first - y.first) * (x.first - y.first) + (x.second - y.second) * (x.second - y.second));
}

int main() {
	ifstream fin("distanta.in");
	ofstream fout("distanta.out");

	fin >> T;
	fout << fixed << setprecision(8);
	while (T -- ) {
		fin >> a >> b >> xi >> yi;
		pair<double, double> p1 = make_pair(xi, (1 - a * xi) / b);
		pair<double, double> p2 = make_pair((1 - b * yi) / a, yi);
		fout << min(dis(p1, make_pair(xi, yi)), dis(p2, make_pair(xi, yi))) << '\n';
	}
	
}
