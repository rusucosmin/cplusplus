#include <fstream>
#include <algorithm>

using namespace std;

ifstream fin("euclid2.in");
ofstream fout("euclid2.out");

int main() {
    int t;
    fin >> t;
    while(t -- ) {
        int x, y;
        fin >> x >> y;
        fout << __gcd(x, y) << '\n';
    }
}
