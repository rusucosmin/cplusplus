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

const char infile[] = "stirling.in";
const char outfile[] = "stirling.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 205;
const int oo = 0x3f3f3f3f;
const int MOD = 98999;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int S[2][MAXN][MAXN];

inline void Stirling() {
    S[0][1][1] = S[1][1][1] = 1;
    for(int i = 2 ; i < MAXN ; ++ i)
        for(int j = 1 ; j <= i ; ++ j) {
            S[0][i][j] = (S[0][i - 1][j - 1] - 1LL * (i - 1) * S[0][i - 1][j]) % MOD;
            S[1][i][j] = (S[1][i - 1][j - 1] + 1LL * j * S[1][i - 1][j]) % MOD;
        }
}

int T;

int main() {
    Stirling();
    for(fin >> T ; T -- ; ) {
        int x, y, z;
        fin >> x >> y >> z;
        fout << S[x - 1][y][z] << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}

