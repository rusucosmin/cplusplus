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

string file = "prefix";

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

char A[MAXN];
int Prefix[MAXN];

inline int Solve() {
    int N, K = 0;
    memset(Prefix, 0, sizeof(Prefix));
    cin >> (A+1);
    N = strlen(A+1);
    Prefix[1] = 0;
    for(int i = 2 ; i <= N ; ++ i) {
        while( K > 0 && A[K + 1] != A[i])
            K = Prefix[K];
        if(A[K+1] == A[i])
            ++ K;
        Prefix[i] = K;
    }
    for(int i = N ; i >= 2 ; -- i)
        if(Prefix[i] && !(i % (i - Prefix[i])))
            return i;
    return 0;
}

int main() {
    int T;
    for(cin >> T ; T ; -- T) {
        cout << Solve() << '\n';
    }
    cin.close();
    cout.close();
    return 0;
}
