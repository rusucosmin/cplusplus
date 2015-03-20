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

const char infile[] = "inversari.in";
const char outfile[] = "inversari.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 5005;
const int MAXM = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

vector <pair<int, int> > where[MAXN];
int ans[MAXM], a[MAXN], dp[MAXN][MAXN], inv[MAXN][MAXN];

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void getInt(int &x) {
    x =0 ;
    while(!isdigit(buff[pos]))
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    while(isdigit(buff[pos])) {
        x = x * 10 + buff[pos] - '0';
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }
}

int N, M;

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    getInt(N);
    getInt(M);
    for(int i = 1 ; i <= N ; ++ i)
        getInt(a[i]);
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        getInt(x);
        getInt(y);
        where[y - x + 1].push_back(make_pair(y, i));
    }
    for(int i = 1 ; i <= N ; ++ i) {
        for(int j = i ; j <= N ; ++ j) {
            inv[i & 1][j] = inv[(i & 1) ^ 1][j];
            if(a[j - i + 1] > a[j])
                ++ inv[i & 1][j];
            dp[i & 1][j] = dp[(i & 1) ^ 1][j - 1] + inv[i & 1][j];
        }
        for(auto it : where[i])
            ans[it.second] = dp[i & 1][it.first];
    }
    for(int i = 1 ; i <= M ; ++ i)
        fout << ans[i] << '\n';

    fin.close();
    fout.close();
    return 0;
}
