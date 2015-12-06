#include <queue>
#include <fstream>
#include <iomanip>

using namespace std;

ifstream fin("dstar.in");
ofstream fout("dstar.out");

double aux, s;
int n, p;
priority_queue <double> q;

int main() {
	fin >> n >> p;
	fin >> aux;
	for(int i = 2 ; i <= n ; ++ i) {
		fin >> aux;
		q.push(aux);
		s += aux;
	}
	q.push(360 - s);
	for(int i = 1 ; i <= p ; ++ i) {
		double act = q.top();
		q.pop();
		q.push(act / 2);
		q.push(act / 2);
	}
	fout << fixed << setprecision(6) << q.top() << '\n';
}
