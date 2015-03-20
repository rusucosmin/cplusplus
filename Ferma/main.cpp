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

const char infile[] = "ferma.in";
const char outfile[] = "ferma.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 10005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, A[MAXN], S[MAXN], K;
int dp[1024][MAXN]; /// costul maxim pentru a face i strageri cu primele j gaini :D

inline int buildDP(const int &st) {
    for(int i = st ; i <= K ; ++ i) {
        int bst = 0;
        for(int j = i ; j <= N ; ++ j) {
            dp[i][j] = max(dp[i][j-1], S[j] + bst);
            bst = max(bst, dp[i - 1][j] - S[j]);
        }
    }
    return dp[K][N];
}

int main() {
    fin >> N >> K;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> A[i];
        S[i] = S[i - 1] + A[i];
    }
    int Ans = buildDP(1);
    for(int i = 1; i <= N ; ++ i)
        dp[1][i] = max(dp[1][i-1], S[i]);
    buildDP(2);
    for(int i = 1 ; i <= N ; ++ i)
        Ans = max(Ans, dp[K][i] + S[N] - S[i]);
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
