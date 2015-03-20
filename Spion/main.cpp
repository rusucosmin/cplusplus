#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>

using namespace std;

const char infile[] = "spion.in";
const char outfile[] = "spion.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MOD = 100003;
const int oo = 0x3f3f3f3f;

char s[MOD];
int P, fact[MOD];

inline int lgPow(int a, int p) {
    int ret = 1;
    for( ; p ; p >>= 1) {
        if(p & 1)
            ret = (1LL * ret * a) % MOD;
        a = (1LL*a * a) % MOD;
    }
    return ret;
}

inline int invMod(const int &x) {
    return lgPow(x, MOD-2);
}

inline void getLoc(int &x, int &y, const char *s) {
    while(*s) {
        ++ x;
        if(*s == 'E')
            ++ y;
        ++ s;
    }
}

int main() {
    fin >> P >> s;
    int x = 1, y = 1;
    getLoc(x, y, s);
    fact[0] = 1;
    for(int i = 1 ; i < MOD ; ++ i)
        fact[i] = (1LL * fact[i - 1] * i) % MOD;
    if(P == 1)
        fout << y << '\n';
    else {
        -- x;
        -- y;
        fout << (1LL * ((1LL * fact[x] * invMod(fact[y])) % MOD) * invMod(fact[x - y])) % MOD << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
