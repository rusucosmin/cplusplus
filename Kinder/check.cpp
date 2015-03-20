#include <fstream>
#include <iostream>

using namespace std ;


int main() {
	ifstream f("kinder.out");
	ifstream g("kinder.ok");
	int x, y;

	int ret = 0;
	int m =0;

	while(f >> x && g >> y) {
		if(x != y)
			cout << x << ' ' << y << '\n', ret ++;
		++ m;
	}
	cout << ret << ' ' << m << '\n';
}
