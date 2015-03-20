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

const char infile[] = "lapte.in";
const char outfile[] = "lapte.out";

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

int dp[MAXN][MAXN], A[MAXN], B[MAXN], dad[MAXN][MAXN], N, L;

inline bool Check(int T) {
    memset(dad, 0, sizeof(dad));
    memset(dp, -oo, sizeof(dp));
    dp[0][0] = 0;
    for(int i = 1 ; i <= N ; ++ i) {
        for(int j = 0 ; j <= L ; ++ j) {
            for(int k = 0 ; k <= j ; ++ k) {
                if(T - (j - k) * A[i] < 0)
                    continue;
                if(dp[i][j] < dp[i - 1][k] + (T - (j - k)* A[i]) / B[i]) {
                    dp[i][j] = dp[i - 1][k] + (T - (j - k)* A[i]) / B[i];
                    dad[i][j] = k;
                }
            }

        }
    }
    return dp[N][L] >= L;
}

inline int binarySearch() {
    int li = 0, ls = 100, ret = -1;
    while(li <= ls) {
        int mid = ((li + ls) >> 1);
        if(Check(mid)) {
            ret = mid;
            ls = mid-1;
        } else li = mid + 1;
    }
    return ret;
}

int main() {
    fin >> N >> L;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> A[i] >> B[i];
    int answer = binarySearch();
    fout << answer << '\n';
    Check(answer);
    for(int i = N, j = L, k ; i ; ) {
        k = dad[i][j];
        A[i] = j - k;
        B[i] = dp[i][j] - dp[i - 1][k];
        j = k;
        -- i;
    }
    for(int i = 1 ; i <= N ; ++ i)
        fout << A[i] << ' ' << B[i] << '\n';
    fin.close();
    fout.close();
    return 0;
}
