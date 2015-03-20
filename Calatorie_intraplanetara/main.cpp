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

string file = "calatorie";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 55;
const int MAXH = 55 * 15;
const long long oo = 1LL << 60;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

long long N, normal[MAXN], super[MAXN];
long long dp[MAXN][MAXH];

inline void Read() {
    cin >> N;
    for(long long i = 1 ; i < N ; ++ i)
        cin >> normal[i] >> super[i];
}

inline long long power(long long j) {
    return j * j * j * j;
}

inline void BuildDynamic() {
    long long Ans = oo;
    memset(dp, 0, sizeof(dp));
    dp[1][0] = 0;
    for(long long i = 2 ; i <= N ; ++ i)
        for(long long j = 0 ; j < MAXH ; ++ j) {
            dp[i][j] = dp[i-1][j] + normal[i-1];
            if( j - super[i-1] >= 0 )
            dp[i][j] = min(dp[i-1][j] + normal[i-1], dp[i-1][j-super[i-1]]);

        }
    /*for(int i = 1 ; i <= N ; ++ i, cout << "\n")
        for(int j = 0 ; j <= MAXH ; ++ j)
            cout << dp[i][j] << ' ';
    */
    Ans = dp[N][0];
    for(long long i = 1 ; i < MAXH ; ++ i)
        Ans = min(Ans, dp[N][i] + i * i * i * i);
    cout << "Consumul minim = "<< Ans << ".\n";
    }

inline void Write() {
}

int main() {
    int T;
    cin >> T;
    while(T -- ) {
        Read();
        BuildDynamic();
        Write();
    }
    cin.close();
    cout.close();
    return 0;
}
