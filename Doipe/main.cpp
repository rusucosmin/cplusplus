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

const char infile[] = "doipe.in";
const char outfile[] = "doipe.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int MOD = 29997;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N;
int dp[2][MAXN];
int T;
char S[MAXN];

/*
    Ideea e urmatoarea:
    dp[i][j] = numarul permutarilor de i elemente cu ultimul element j si care satisface primele i - 1 semne
*/

int main() {
    fin >> T;
    while(T -- ) {
        fin >> N >> (S + 1);
        dp[1][1] = 1;
        for(int i = 2 ; i <= N ; ++ i) {
            bool act = i & 1;
            bool last = (i & 1) ^ 1;
            for(int j = 1 ; j <= i ; ++ j) {
                dp[act][j] = 0;
                if(S[i - 1] == '<')
                    dp[act][j] += dp[last][j - 1];
                else dp[act][j] += (dp[last][i - 1] - dp[last][j - 1] + MOD);
                while(dp[act][j] >= MOD)
                    dp[act][j] -= MOD;
                dp[act][j] += dp[act][j-1];
                while(dp[act][j] >= MOD)
                    dp[act][j] -= MOD;
            }
        }
        fout << dp[N & 1][N] << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
