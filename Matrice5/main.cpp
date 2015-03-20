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

const char infile[] = "matrice5.in";
const char outfile[] = "matrice5.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int MOD = 10007;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

inline int lgPow(int N, int P) {
    int Ans = 1;
    for( ; P ; P >>= 1) {
        if(P & 1)
            Ans = (1LL * Ans * N) % MOD;
        N = (1LL * N * N) % MOD;
    }
    return Ans;
}

inline int Solve(int N, int M, int P, int K) {
    return (1LL * lgPow(K * P, (N - 1) * (M - 1)) * lgPow(P, (N + M - 1))) % MOD;
}

int main() {
    int T, N, M, P, K;
    for(fin >> T ; T-- ; ) {
        fin >> N >> M >> P >> K;
        fout << Solve(N, M, P, K) << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
