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

const char infile[] = "functii.in";
const char outfile[] = "functii.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 10005;
const int MOD = 30103;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

inline long long lgPow(long long n, long long k) {
    long long Ans = 1;
    for( ; k ; k >>= 1) {
        if(k & 1)
            Ans = (1LL * Ans * n) % MOD;
        n = (1LL * n * n) % MOD;
    }
    return Ans;
}

inline long long inv(long long fact, long long mod) {
    return lgPow(fact, mod - 2);
}

long long N, K, fact[MAXN];

int main() {
    fin >> N >> K;
    fact[0] = fact[1] = 1;
    for(int i = 2 ; i <= N ; ++ i)
        fact[i] = (1LL * fact[i - 1] * i) % MOD;
    /// C(n , k) = N! / (K! * (n - K)!
    long long invK = inv(fact[K], MOD);
    long long invNk = inv(fact[N - K], MOD);
    long long comb = (1LL * fact[N] * invK * invNk) % MOD;
    fout << (1LL * ( lgPow(2, K) - 2) * comb) % MOD << '\n';
    fin.close();
    fout.close();
    return 0;
}
