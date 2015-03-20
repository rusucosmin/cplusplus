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

const char infile[] = "drumuri3.in";
const char outfile[] = "drumuri3.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100;
const int MOD = 10007;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, K, Q;
int G[MAXN][MAXN], rez[MAXN][MAXN], B[MAXN][MAXN], aux[MAXN][MAXN];
int I[MAXN][MAXN];

inline void Add(int a[][MAXN], int b[][MAXN]) {
    for(int i = 0 ; i < N ; ++ i)
        for(int j = 0 ; j < N ; ++ j) {
            a[i][j] += b[i][j];
            if(a[i][j] >= MOD)
                a[i][j] -= MOD;
        }
}

inline void Multiply(int a[][MAXN], int b[][MAXN], int c[][MAXN]) {
    memset(c, 0, sizeof(c));
      for(int i = 0 ; i < N ; ++ i)
            for(int j = 0 ; j < N ; ++ j) {
                c[i][j] = 0;
                for(int k = 0 ; k < N ; ++ k)
                    c[i][j] = (c[i][j] + 1LL * a[i][k] * b[k][j]) % MOD;
            }
}

inline void lgPut(const int &K) {
    int c[MAXN][MAXN];
    memcpy(rez, I, sizeof(rez));
    memcpy(c, G, sizeof(c));
    for(int i = 0 ; (1 << i) <= K ; ++ i) {
        if((1 << i) & K) {
            Multiply(rez, c, aux);
            memcpy(rez, aux, sizeof(rez));
        }
        Multiply(c, c, aux);
        memcpy(c, aux, sizeof(aux));
    }
}

inline void Solve(const int &K) {
    memset(rez, 0, sizeof(rez));
    if(K == 0)
        return ;
    if(K & 1) {
        Solve(K - 1);
        lgPut(K);
        Add(B, rez);
    }
    else {
        Solve(K / 2);
        lgPut(K / 2);
        Add(rez, I);
        Multiply(B, rez, aux);
        memcpy(B, aux, sizeof(B));
    }
}

int main() {
    fin >> N >> M >> K >> Q;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        fin >> x >> y;
        -- x;
        -- y;
        G[x][y] = 1;
        G[y][x] = 1;
    }
    for(int i = 0 ; i < N ; ++ i)
        I[i][i] = 1;
    Solve(K - 1);
    for(int i = 1 ; i <= Q ; ++ i) {
        int x, y;
        fin >> x >> y;
        -- x; -- y;
        fout << B[x][y] << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
