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

const char infile[] = "matrice8.in";
const char outfile[] = "matrice8.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 35;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int dp[MAXN][MAXN][MAXN][MAXN];
int T, N, M;
char s[MAXN][MAXN];

int memo(int i, int j, int n, int m) {
    if(dp[i][j][n][m] != -1)
        return dp[i][j][n][m];
    bool allthesame = 1;
    for(int x = i ; x <= n; ++ x)
        for(int y = j ; y <= m ; ++ y)
            allthesame &= (s[x][y] == s[i][j]);
    if(allthesame) {
        dp[i][j][n][m] = 0;
        return 0;
    }
    int ret = oo;
    for(int l = i ; l < n ; ++ l)
        ret = min(ret, 1 + memo(i, j, l, m) + memo(l + 1, j, n, m));
    for(int c = j ; c < m ; ++ c)
        ret = min(ret, 1 + memo(i, j, n, c) + memo(i, c+1, n, m));
    dp[i][j][n][m] = ret;
    return ret;
}

int main() {
    fin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        memset(dp, -1, sizeof(dp));
        fin >> N >> M;
        for(int i = 1 ; i <= N ; ++ i)
            fin >> (s[i] + 1);
        fout << memo(1, 1, N, M) << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
