#include <fstream>
#include <algorithm>
using namespace std;
int main()
{
    ifstream fin("euclid2.in");
    ofstream fout("euclid2.out");
    int t;
    fin >> t;
    for(int tes = 1 ; tes <= t; ++ tes) {
        int x, y;
        fin >> x >> y;
        fout << __gcd(x, y) << '\n';
    }
    return 0;
}
