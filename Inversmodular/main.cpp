#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

ifstream fin("inversmodular.in");
ofstream fout("inversmodular.out");

int a, n;

inline void gcd(int a, int b, int &x, int &y) {
    if(!b) {
        x = 1;
        y = 0;
        return;
    }
    int x0, y0;
    gcd(b, a % b, x0, y0); /// bx0 + (a - b*(a/b)) * y0 = ax + by  <=> a(y0 - x) + b(x0 - (a/b)*y0 - y) = 0
    x = y0;
    y = x0 - (a / b) * y0;
}

int main() {
    /// a * x + n * y = 1;
    int x, y;
    fin >> a >> n;
    gcd(a, n, x, y);
    x %= n;
    while(x < 0)
        x += n;
    fout << x << '\n';
}
