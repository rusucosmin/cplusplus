#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

int main (){
	ifstream fin("aria.in");
	ofstream fout("aria.out");
	vector <pair<double, double> > v;
	int n;
	fin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		double x, y;
		fin >> x >> y;
		v.push_back(make_pair(x, y));
	}
	v.push_back(*v.begin());
	double area = 0;
	for(int i = 0 ; i < n ; ++ i)
		area = area + (v[i].first * v[i + 1].second - v[i + 1].first * v[i].second);
	fout << fixed << setprecision(6) << area * 0.5 << '\n';
}
