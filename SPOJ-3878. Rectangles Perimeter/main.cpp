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

int n, dp[MAXN][2], a[MAXN], b[MAXN];

int main() {

    cin >> n;
    cin >> a[1] >> b[1];
    dp[1][0] = b[1];
    dp[1][1] = a[1];
    for(int i = 2 ; i <= n ; ++ i) {
        cin >> a[i] >> b[i];
        dp[i][0] = b[i] + max(dp[i - 1][0] + abs(a[i] - a[i - 1]), dp[i - 1][1] + abs(a[i] - b[i - 1]));
        dp[i][1] = a[i] + max(dp[i - 1][0] + abs(b[i] - a[i - 1]), dp[i - 1][1] + abs(b[i] - b[i - 1]));
    }
    cout << max(dp[n][0], dp[n][1]) << '\n';
    fin.close();
    fout.close();
    return 0;
}
