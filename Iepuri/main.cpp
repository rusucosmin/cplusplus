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

const char infile[] = "iepuri.in";
const char outfile[] = "iepuri.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;
const int MOD = 666013;

typedef int Matrix[4][4];
typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int X, Y, Z, A, B, C;

inline void Multiply(Matrix A, Matrix B) {
    Matrix M;
    memset(M, 0, sizeof(M));
    for(int i = 1 ; i <= 3 ; ++ i)
        for(int j = 1 ; j <= 3 ; ++ j)
            for(int k = 1 ; k <= 3 ; ++ k)
                M[i][j] = (M[i][j] + 1LL * A[i][k] * B[k][j]) % MOD;
    memcpy(A, M, sizeof(M));
}

inline int lgPow(int N) {
    Matrix Ans, I;
    memset(Ans, 0, sizeof(Ans));
    memset(I, 0, sizeof(I));
    Ans[1][2] = Ans[2][3] = 1;
    Ans[3][1] = C;
    Ans[3][2] = B;
    Ans[3][3] = A;

    I[1][1] = 1;
    I[2][2] = 1;
    I[3][3] = 1;

    for(; N ; N >>= 1) {
        if(N & 1)
            Multiply(I, Ans);
        Multiply(Ans, Ans);
    }
    return (1LL * I[3][1] * X + 1LL * I[3][2] * Y + 1LL * I[3][3] * Z) % MOD;
}

int main() {
    int N, T;
    fin >> T;
    for(int i = 1 ; i <= T ; ++ i) {
        fin >> X >> Y >> Z >> A >> B >> C >> N;
        fout << lgPow(N - 2) << '\n';
    }
    return 0;
}
