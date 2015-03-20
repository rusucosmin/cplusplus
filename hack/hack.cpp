#include <fstream>

using namespace std;

int main() {
	ofstream cout("hack.in");
	cout << "10000 5 999999999\n";
	for(int i = 1 ; i <= 10000 ; ++ i, cout << '\n')
		for(int j = 1 ; j <= 5 ; ++ j)
			cout << 1 << ' ';
}
