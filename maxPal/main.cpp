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

const char infile[] = "maxpal.in";
const char outfile[] = "maxpal.out";

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

short N, a[MAXN];
int dp[2][MAXN];
int nr[2][MAXN];

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> a[i];
    dp[N & 1][N] = 1;
    nr[N & 1][N] = 1;
    for(int i = N - 1 ; i >= 1 ; -- i) {
        bool cur = i & 1;
        bool last = cur ^ 1;
        memset(dp[cur], 0, sizeof(dp[cur]));
        memset(nr[cur], 0, sizeof(nr[cur]));
        dp[cur][i] = 1;
        nr[cur][i] = 1;
        if(a[i] == a[i + 1]) {
            dp[cur][i + 1] = 2;
            nr[cur][i + 1] = 1;
        }
        else {
            dp[cur][i + 1] = 1;
            nr[cur][i + 1] = 2;
        }
        for(int j = i + 2 ; j <= N ; ++ j) {
            if(a[i] == a[j]) {
                dp[cur][j] = 2 + dp[last][j - 1];
                nr[cur][j] = nr[last][j - 1];
                if(dp[cur][j] == dp[cur][j - 1])
                    nr[cur][j] += nr[cur][j - 1];
                if(dp[cur][j] == dp[last][j])
                    nr[cur][j] += nr[last][j];
            }
            else {
                /// dp[i][j] = lg maxima intre i si j
                if(dp[cur][j - 1] == dp[last][j]) {
                    dp[cur][j] = dp[cur][j - 1];
                    nr[cur][j] = nr[cur][j - 1] + nr[last][j];
                    if(dp[cur][j] == dp[last][j - 1])
                        nr[cur][j] -= nr[last][j - 1];
                }
                else {
                    if(dp[cur][j - 1] > dp[last][j]) {
                        dp[cur][j] = dp[cur][j - 1];
                        nr[cur][j] = nr[cur][j - 1];
                    }
                    else {
                        dp[cur][j] = dp[last][j];
                        nr[cur][j] = nr[last][j];
                    }
                }
            }
            nr[cur][j] %= 666013;
            if(nr[cur][j] < 0)
                nr[cur][j] += 666013;
        }
    }
    fout << dp[1][N] << ' ' << nr[1][N] << '\n';
    fin.close();
    fout.close();
    return 0;
}
