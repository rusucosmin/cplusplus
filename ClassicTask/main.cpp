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

const char infile[] = "classictask.in";
const char outfile[] = "classictask.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

long long A, B, MOD;

inline long long mulLog(long long N, long long X) {
    long long s = 0;
    for ( ; X ; X >>= 1) {
        if(X & 1)
            s = (s + N) % MOD;
        N = (N + N) % MOD;
    }
    return s;
}

inline long long lgPow(long long A, long long B) {
    long long Ans = 1;
    for( ; B ; B >>= 1) {
        if(B & 1)
            Ans = mulLog(Ans, A);
        A = mulLog(A, A);
    }
    return Ans;
}

int main() {
    fin >> A >> B >> MOD;
    fout << lgPow(A, B) << '\n';
    fin.close();
    fout.close();
    return 0;
}
