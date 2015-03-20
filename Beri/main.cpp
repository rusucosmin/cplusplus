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
#include <cassert>
 
using namespace std;
 
string file = "beri";
 
ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );
 
const int MAXN = 1000005;
const int oo = (1<<31)-1;
 
typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;
 
const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }
 
struct ClassComp {
    inline bool operator () (const int &a, const int &b) const {
        return a > b;
    }
};
 
int N, K, Q, X, Y, Z;
long long beri[MAXN];
 
int main() {
    cin >> N >> K;
    cin >> Q >> X >> Y >> Z;
    int last = Q;
    beri[1] = last;
    for(int i = 2 ; i <= N ; ++ i)  {
        long long act = (1LL * last * 1LL * X + 1LL * Y) % Z + K;
        beri[i] = act;
        last = act;
    }
    long long Ans = 0;
    nth_element(beri + 1, beri + N - K + 1 , beri + N + 1);
    for(int i = N - K + 1 ; i <= N ; ++ i)
        Ans += 1LL * beri[i];
    cout << Ans - (1LL * K * ( K - 1 ) / 2)   << '\n';
    cin.close();
    cout.close();
    return 0;
}
