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

const char infile[] = "xnumere.in";
const char outfile[] = "xnumere.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int MOD = 666013;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

long long K, N;
int X;
int fact[MAXN];

int lgPow(int a, long long p) {
    int ans = 1;
    a %= MOD;
    for( ; p ; p >>= 1) {
        if(p & 1)
            ans = (1LL * ans * a) % MOD;
        a = (1LL * a * a) % MOD;
    }
    return ans;
}

int invMod(int x) {
    return lgPow(x, MOD - 2);
}

int main() {
    fin >> K >> X >> N;
    int COMB = 1, SOL = 0;
    for(int i = 0 ; i <= X ; ++ i) {
        if(i >= 1) {
            COMB = (1LL * COMB * (X - i + 1)) % MOD;
            COMB = (1LL * COMB * lgPow(i, MOD - 2)) % MOD;
        }
        int tmp = (1LL * COMB * lgPow(i, N)) % MOD;
        if((X - i) % 2 == 0) {
            SOL += tmp;
            if(SOL >= MOD)
                SOL -= MOD;
        }
        else {
            SOL -= tmp;
            if(SOL < 0)
                SOL += MOD;
        }
    }
    long long P;
    for(P = K - X + 1 ; P <= K ; ++ P)
        SOL = (1LL * SOL * (P % MOD)) % MOD;
    for(P = 1 ; P <= X ; ++ P)
        SOL = (1LL * SOL * lgPow(P, MOD - 2)) % MOD;
    fout << SOL << '\n';
    fin.close();
    fout.close();
    return 0;
}
