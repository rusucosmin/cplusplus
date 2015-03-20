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

const char infile[] = "trmax.in";
const char outfile[] = "trmax.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 2005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, K, A[MAXN][MAXN];
int dp[MAXN][MAXN];

int main() {
    fin >> N >> M >> K;
    for(int i = 1 ; i <= K ; ++ i) {
        int x, y;
        fin >> x >> y;
        A[x][y] = 1;
    }
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= M ; ++ j)
            if(A[i][j] == 0)
                A[i][j] = A[i][j - 1] + 1;
            else A[i][j] = 0;
    ///memset(dp, oo, sizeof(dp));
    int Ans = 0;
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= M ; ++ j) {
            dp[i][j] = min(dp[i - 1][j - 1] + 1, (A[i][j] + 1) / 2);
            Ans = max(Ans, dp[i][j]);
        }
    fout << Ans * Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
