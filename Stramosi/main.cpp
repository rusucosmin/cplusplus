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

const char infile[] = "stramosi.in";
const char outfile[] = "stramosi.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 250005;
const int MAXLG = 25;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int dp[MAXLG][MAXN];

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void get(int &x) {
    x = 0;
    while(!('0' <= buff[pos] && buff[pos] <= '9'))
        if(++ pos == lim) {
            fread(buff, 1, lim, stdin);
            pos = 0;
        }
    while('0' <= buff[pos] && buff[pos] <= '9') {
        x = x * 10 + buff[pos] - '0';
        if(++ pos == lim) {
            fread(buff, 1, lim, stdin);
            pos = 0;
        }
    }
}

inline int Query(int x, int y) {
    for(int lg = 0 ; (1 << lg) <= y ; ++ lg)
        if(y & (1 << lg))
            x = dp[lg][x];
    return x;
}

int main() {
    int N, M;
    freopen(infile, "r", stdin);
    get(N);
    get(M);
    for(int i = 1 ; i <= N ; ++ i)
        get(dp[0][i]);
    for(int lg = 1 ; lg <= 20 ; ++ lg)
        for(int i = 1 ; i <= N ; ++ i)
            dp[lg][i] = dp[lg - 1][dp[lg - 1][i]];
    for(int i = 1 ; i <= M ; ++ i) {
        int P, Q;
        get(P);
        get(Q);
        fout << Query(P, Q) << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
