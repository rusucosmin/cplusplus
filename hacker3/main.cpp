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

const char infile[] = "hacker3.in";
const char outfile[] = "hacker3.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const long long oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

long long dp[2][MAXN];
int N;

int main() {
    long long a, b;
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> a >> b;
        dp[(i & 1)][0] = dp[(i & 1) ^ 1][0] + b;
        for(int j = 1 ; j <= 32 && j <= i ; ++ j) {
            dp[i & 1][j] = dp[(i & 1) ^ 1][j - 1] + a * (1LL << (j - 1));
            if(j < i)
                dp[i & 1][j] = min(dp[i & 1][j], dp[(i & 1) ^ 1][j] + b * (1LL << j));
        }
    }
    if(!dp[N & 1][0])
        dp[N & 1][0] = oo;
    for(int i = 0 ; i <= 32 ; ++ i)
        if(dp[N & 1][i])
            dp[N & 1][0] = min(dp[N & 1][0], dp[N & 1][i]);
    fout << dp[N & 1][0] << '\n';
    fin.close();
    fout.close();
    return 0;
}
