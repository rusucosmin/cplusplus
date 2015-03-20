#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

ifstream fin("euclid3.in");
ofstream fout("euclid3.out");

inline int gcd(int a, int b, int &x, int &y) {
    if(!b) {
        x = 1;
        y = 0;
        return a;
    }
    int x0, y0;
    int _gcd = gcd(b, a % b, x0, y0);
    /// a = b * (a / b) + a % b
    /// b*x0 + (a - b * q)y0 = ax + by;       a(y0 - x) + b(x0 - q*y0 - y) = 0
    x = y0;
    y = x0 - (a / b) * y0;
    return _gcd;
}

int main() {
    int t;
    fin >> t;
    while(t -- ) {
        int a, b, c;
        fin >> a >> b >> c;
        int x, y;
        int _gcd = gcd(a, b, x, y);
        if(c % _gcd)
            fout << "0 0\n";
        else
            fout << x * (c / _gcd) << ' ' << y * (c / _gcd) << '\n';
    }

}
