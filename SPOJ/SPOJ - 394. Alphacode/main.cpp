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

const int MAXN = 5005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

char s[MAXN + 2];
unsigned long long dp[MAXN + 2];

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    while(cin.getline(s + 1, MAXN)) {
        if(s[1] == '0')
            break;
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        int n = strlen(s + 1);
        if(n < 2) {
            cout << "1\n";
            continue;
        }
        for(int i = 1 ; i <= n ; ++ i) {
            if(s[i] == '0') {
                dp[i] = 0;
                continue;
            }
            dp[i] = dp[i - 1];
            if(s[i - 1] == '1' || (s[i - 1] == '2' && s[i] <= '6'))
                dp[i] += dp[i - 2];
        }
        cout << dp[n] << '\n';
    }
    return 0;
}
