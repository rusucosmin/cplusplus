#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("lgput.in");
ofstream fout("lgput.out");

const int mod = 1999999973;

inline int lgpow(int a, int b) {
    int ans = 1;
    a %= mod;
    for( ; b ; b >>= 1) {
        if(b & 1)
            ans = (1LL * ans * a) % mod;
        a = (1LL * a * a) % mod;
    }
    return ans;
}

int main() {
    int a, b;
    fin >> a >> b;
    fout << lgpow(a, b) << '\n';
}
