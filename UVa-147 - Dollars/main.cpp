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

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

long long dp[300 * 100 + 10];
int c[] = { 5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000 };

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    dp[0] = 1;
    for(int i = 0 ; i < 11 ; ++ i)
        for(int j = c[i] ; j <= 30000 ; ++ j)
            dp[j] += dp[j - c[i]];
    int x, y;
    double s;
    while(true) {
        scanf("%lf", &s);
        if(s == 0)
            break;
        printf("%6.2f%17ld\n", s, dp[(int) round(s * 100)]);
    }
    fin.close();
    fout.close();
    return 0;
}
