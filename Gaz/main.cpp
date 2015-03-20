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

string file = "gaz";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 2005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(long long &a, const long long b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct ClassComp {
    inline bool operator () (const int &a, const int &b) const {
        return a > b;
    }
};

long long L, P, D, C, N, G[MAXN];
vector<long long> DP(MAXN, oo);

int main() {
    cin >> L >> P >> D >> C;
    cin >> N;
    for(int i = 1 ; i <= N ; ++ i)
        cin >> G[i], G[0] += G[i];
    DP[0] = 0;
    for(long long i = 1 ; i <= N ; ++ i) {
        int extra = 0, gasoline = G[i];
        for(long long j = i - 1 ;  j >= 0 ; -- j) {
            Get_min(DP[i], DP[j] + extra * C + P);
            gasoline += G[j];
            extra += max((long long) 0, gasoline - G[j] - L);
        }
    }
    cout << DP[N] + G[0]*D << '\n';
    cin.close();
    cout.close();
    return 0;
}
