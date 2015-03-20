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

const char infile[] = "joc.in";
const char outfile[] = "joc.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, a[MAXN][MAXN], dp[MAXN][MAXN];

int main() {
    fin >> N >> M;
    memset(dp, -oo, sizeof(dp));
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= M ; ++ j)
            fin >> a[i][j];
    dp[1][1] = a[1][1];
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1; j <= M ; ++ j) {
            if(i == 1 && j == 1)
                continue;
            a[i][j] -= max(dp[i - 1][j], dp[i][j - 1]);
            dp[i][j] = max(a[i][j], max(dp[i - 1][j], dp[i][j - 1]));
        }
    a[0][0] = -oo;
    pair<int, int> Ans = make_pair(0, 0);
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= M ; ++ j)
            if(a[Ans.first][Ans.second] < a[i][j])
                Ans = make_pair(i, j);
    fout << a[Ans.first][Ans.second] << ' ' << Ans.first << ' ' << Ans.second << '\n';
    fin.close();
    fout.close();
    return 0;
}
