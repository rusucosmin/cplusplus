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

const char infile[] = "redu.in";
const char outfile[] = "redu.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 505;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, cost[100][100], dp[MAXN][MAXN];
char s[MAXN];

inline int getCost(const int &i, const int &j) {
    if(i > j)
        return 0;
    return dp[i][j];
}

inline int solve() {
    /// dp[i][j] = costul minim de a elimina secventa i->j
    /// dp[i][i + 1] = cost s[i] , s[i + 1], logic
    memset(dp, oo, sizeof(dp));
    for(int i = 0 ; i + 1 < N ; ++ i)
        dp[i][i+1] = cost[s[i] - 'a'][s[i + 1] - 'a'];
    for(int nr = 2 ; nr < N ; ++ nr) {
        for(int i = 0 ; i + nr < N ; ++ i) {
            int j = i + nr;
            if((j - i + 1) % 2)
                continue;
            for(int k = i + 1 ; k <= j ; ++ k)
                dp[i][j] = min(dp[i][j], cost[s[i]-'a'][s[k]-'a'] + getCost(i + 1, k - 1) + getCost(k + 1, j));
        }
    }
    return dp[0][N - 1];
}

int main() {
    fin >> N >> s;
    for(int i = 0 ; i < 26 ; ++ i)
        for(int j = 0 ; j < 26 ; ++ j)
            fin >> cost[i][j];
    fout << solve() << '\n';
    fin.close();
    fout.close();
    return 0;
}
