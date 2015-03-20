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

const int MAXN = 705;
const int MAXG = 1010;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

int T, A, B, N;
int a, b, c;
int dp[MAXG][MAXG];

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        cin >> A >> B >> N;
        int Ans = oo;
        memset(dp, oo, sizeof(dp));
        dp[0][0] = 0;
        for(int i = 1 ; i <= N ; ++ i) {
            cin >> a >> b >> c;
            for(int j = 4 * A ; j >= 0 ; -- j)
                for(int k = 4 * B ; k >= 0 ; -- k)
                    if(dp[j][k] != oo) {
                        dp[j + a][k + b] = min(dp[j + a][k + b], dp[j][k] + c);
                        if(j + a >= A && k + b >= B)
                            Ans = min(Ans, dp[j + a][k + b]);
                    }
        }
        cout << Ans << '\n';
    }
    return 0;
}
