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

const char infile[] = "input.in";
const char outfile[] = "output.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 105;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

char A[MAXN], B[MAXN], C[MAXN], dp[MAXN][MAXN][MAXN], t[3][MAXN][MAXN][MAXN];
int N, M, P, Pi[MAXN];
bool put[MAXN][MAXN][MAXN];
int sti, stj, stk, result;

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> (A + 1) >> (B + 1) >> (C + 1);
    N = strlen(A + 1);
    M = strlen(B + 1);
    P = strlen(C + 1);
    int invariant = 0;
    for(int i = 2 ; i <= P ; ++ i) {
        while(invariant > 0 && C[i] != C[invariant + 1])
            invariant = Pi[invariant];
        if(C[i] == C[invariant + 1])
            ++ invariant;
        Pi[i] = invariant;
    }
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= M ; ++ j) {
            for(int k = 0 ; k <= P ; ++ k) {
                if(dp[i-1][j][k] > dp[i][j-1][k]) {
                    dp[i][j][k] = dp[i-1][j][k];
                    t[0][i][j][k] = i-1;
                    t[1][i][j][k] = j;
                    t[2][i][j][k] = k;
                }
                else {
                    dp[i][j][k] = dp[i][j-1][k];
                    t[0][i][j][k] = i;
                    t[1][i][j][k] = j-1;
                    t[2][i][j][k] = k;
                }
            }
            if(A[i] == B[j]) {
                for(int k = 0 ; k <= P ; ++ k) {
                    int invariant = k;
                    while(invariant > 0 && A[i] != C[invariant + 1])
                        invariant = Pi[invariant];
                    if(A[i] == C[invariant + 1])
                        ++ invariant;
                    if(invariant == P)
                        continue;
                    if(dp[i-1][j-1][k] + 1 > dp[i][j][invariant]) {
                        dp[i][j][invariant] = 1 + dp[i-1][j-1][k];
                        t[0][i][j][invariant] = i-1;
                        t[1][i][j][invariant] = j-1;
                        t[2][i][j][invariant] = k;
                        put[i][j][invariant] = true;
                        if(result < dp[i][j][invariant]) {
                            result = dp[i][j][invariant];
                            sti = i;
                            stj = j;
                            stk = invariant;
                        }
                    }
                }
            }
       }
    string ret = "";
    while(sti) {
        if(put[sti][stj][stk])
            ret += A[sti];
        int i = sti, j = stj, k = stk;
        sti = t[0][i][j][k];
        stj = t[1][i][j][k];
        stk = t[2][i][j][k];
    }
    reverse(ret.begin(), ret.end());
    if(!result)
        cout << "0\n";
    else
        cout << ret << '\n';
    fin.close();
    fout.close();
    return 0;
}
