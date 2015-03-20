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

const char infile[] = "shift.in";
const char outfile[] = "shift.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

char s[MAXN], x[60];
int N;
int dp[MAXN][2];
int pos[MAXN][2];
int cost[MAXN][2];

inline int getCode(char &s) {
    return s - 'a' + 1;
}

int main() {
    fin >> (s + 1);
    int ind = 0;
    for(int i = 1 ; i <= 26 * 2 ; ++ i) {
        if(i % 2)
            ++ ind;
        fin >> x[i];
        int idx = getCode(x[i]);
        if(!pos[idx][0])
            pos[idx][0] = ind;
        else
            pos[idx][1] = ind;
    }
    for(int i = 1 ; i <= 26 * 2 ; ++ i) {
        int val;
        fin >> val;
        int idx = getCode(x[i]);
        if(!cost[idx][0])
            cost[idx][0] = val;
        else
            cost[idx][1] = val;
    }
    N = strlen(s + 1);
    int idx, lastidx;
    idx = getCode(s[1]);
    dp[1][0] = cost[idx][0] + pos[idx][0] - 1;
    dp[1][1] = cost[idx][1] + pos[idx][1] - 1;
    for(int i = 2 ; i <= N ; ++ i) {
        idx = getCode(s[i]);
        lastidx = getCode(s[i - 1]);
        /// dp[i][0]
        dp[i][0] = cost[idx][0] + min(dp[i - 1][0] + abs(pos[lastidx][0] - pos[idx][0]), dp[i - 1][1] + abs(pos[lastidx][1] - pos[idx][0]));
        dp[i][1] = cost[idx][1] + min(dp[i - 1][0] + abs(pos[lastidx][0] - pos[idx][1]), dp[i - 1][1] + abs(pos[lastidx][1] - pos[idx][1]));
    }
    fout << min(dp[N][0], dp[N][1]) << '\n';
    fin.close();
    fout.close();
    return 0;
}
