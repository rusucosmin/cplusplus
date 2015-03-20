#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <cstring>
#include <string>
#include <stack>
#include <deque>
#include <iomanip>
#include <set>
#include <map>
#include <cassert>
#include <ctime>
#include <list>
#include <iomanip>

using namespace std;

string file = "mmo";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 19;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int dp[2][(1 << MAXN)], N, M, totalCost;

int main() {
    cin >> N >> M;
    memset(dp, oo, sizeof(dp));
    int maxConf = (1 << N);
    dp[0][maxConf - 1] = 0; /// merg pe fiecare muchie, iar apoi revni pe acelasi => se anuleaza costurile
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        cin >> x >> y >> z;
        totalCost += z;
        -- x;
        -- y;
        for(int conf = 0 ;conf < maxConf ; ++ conf) {
            int newConf = conf ^ (1 << x) ^ (1 << y);
            dp[1][newConf] = min(dp[1][newConf], dp[0][conf]);
            dp[1][conf] = min(dp[1][conf], dp[0][conf] + z);
        }
        for(int conf = 0 ; conf < maxConf ; ++ conf)
            dp[0][conf] = dp[1][conf], dp[1][conf] = oo;
    }
    cout << totalCost - dp[0][maxConf - 1] << '\n';
    cin.close();
    cout.close();
    return 0;
}
