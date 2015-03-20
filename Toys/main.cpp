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

const char infile[] = "toys.in";
const char outfile[] = "toys.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 2000005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, L, T[MAXN], S, X, Y, Z, V;

int main() {
    cin.sync_with_stdio(false);
    fin >> N >> L >> M;
    fin >> S >> X >> Y >> Z >> V;
    T[1] = L + S;
    int last_d = S, d, t = 1LL;
    for(int i = 2 ; i <= N ; ++ i) {
        d = ( 1LL * X * last_d + 1LL * Y * ( i - 1 ) ) % ( L - 1 ) + 1;
        t = ( 1LL * Z * last_d + 1LL * V * ( i - 1 ) ) % 2;
        if(t) T[i] = L + d;
        else T[i] = L - d;
        last_d = d;
    }
    nth_element(T + 1, T + (M-1)%N + 1, T + N + 1);
    fout << 1LL * T[(M - 1)%N + 1] + ((M+N-1)/N - 1) * 2LL * L + 1LL*L << '\n';
    fin.close();
    fout.close();
    return 0;
}
