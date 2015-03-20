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

const char infile[] = "concert2.in";
const char outfile[] = "concert2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 2505;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, K1, K2;
int a[MAXN];
int dp[MAXN][303][303];
int ans = 0;
/// dp[i][k1][k2] = lg max din primele i numere astfel incat pe ultima pozitie sa am a[i] so k1 crescatoare si k2 descrecatoare

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    fin >> N >> K1 >> K2;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> a[i];
    for(int i = 1 ; i <= N ; ++ i) {
        for(int j = 1 ; j < i ; ++ j)
            for(int k1 = 1 ; k1 <= K1 ; ++ k1)
                for(int k2 = 1 ; k2 <= K2 ; ++ k2) {
                    if(a[j] <= a[i]) {
                        dp[i][k1][k2] = max(1 + dp[j][k1 - 1][k2], dp[i][k1][k2]);
                        ans = max(ans, dp[i][k1][k2]);
                    }
                    if(a[j] >= a[i]) {
                        dp[i][k1][k2] = max(1 + dp[j][k1][k2 - 1], dp[i][k1][k2]);
                        ans = max(ans, dp[i][k1][k2]);
                    }
                }
    }
    fout << ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
