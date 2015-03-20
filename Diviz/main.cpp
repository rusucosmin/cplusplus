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

const char infile[] = "diviz.in";
const char outfile[] = "diviz.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 205;
const int MAXK = 105;
const int MOD = 30103;
const int SIGMA = 10;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

/**
    dp[i][j][k] = numarul subsirurilor distincte de lungime i care contine ca ultima cifra cea de-a
    j-a cifra a lui N si dau restul k la inpartirea cu K
    */

int K, A, B, sz, Ans, u;
int dp[2][MAXN][MAXK], nxt[SIGMA][MAXN], rst[MAXK][SIGMA];
char N[MAXN];

inline void getMOD(int &a) {
    if(a >= MOD)
        a -= MOD;
}

int main() {
    fin >> K >> A >> B;
    fin >> (N + 1);
    sz = strlen(N + 1);
    for(int i = 0 ; i < K ; ++ i)
        for(int j = 0 ; j < 10 ; ++ j)
            rst[i][j] = (i * 10 + j) % K;
    for(int i = sz ; i > 0 ; -- i)
        for(int j = 9 ; j >= 0 ; -- j) {
            if(N[i] - '0' == j)
                nxt[j][i] = i;
                else nxt[j][i] = nxt[j][i+1];
                //fout << nxt[j][i] << ' ';
            }
    for(int i = 1 ; i < 10 ; ++ i)
        dp[0][nxt[i][1]][i % K] = 1;
    for(int i = 1 ; i <= B ; ++ i, u ^= 1) {
        for(int j = i ; j <= sz ; ++ j) {
            if(i >= A) {
                Ans += dp[u][j][0];
                getMOD(Ans);
            }
            for(int r = 0 ; r < K ; ++ r) {
                for(int cif = 0 ; cif < 10 ; ++ cif) {
                    dp[u ^ 1][nxt[cif][j + 1]][rst[r][cif]] += dp[u][j][r];
                    getMOD(dp[u ^ 1][nxt[cif][j + 1]][rst[r][cif]]);
                }
            }
        }
        memset(dp[u], 0, sizeof(dp[u]));
    }
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
