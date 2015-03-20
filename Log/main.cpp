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

string file = "log";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 10005;
const int oo = 0x3f3f3f3f;

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

int N, t1, t2, t3;
int a[MAXN], b[MAXN], S[MAXN];

int main() {
    cin >> N >> t1 >> t2 >> t3;
    memset(S, oo, sizeof(S));
    S[0] = N*t2 - t1;
    for(int i = 1 ; i <= N ; ++ i) {
        cin >> a[i] >> b[i];
        for(int j = i ; j > 0 ; -- j) {
            if( j < i && b[j] != a[j + 1])
                break;
            Get_min(S[i], S[j-1] + t3 * (a[j]-b[i])*(a[j]-b[i]) + t1 - t2);
        }
    }
    cout << S[N] << '\n';
    cin.close();
    cout.close();
    return 0;
}
