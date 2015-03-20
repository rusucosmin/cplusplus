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

string file = "reguli";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 500005;
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

long long N, A[MAXN], Prefix[MAXN], K;

inline void BuildPrefix() {
    Prefix[1] = 0;
    for(int i = 2 ; i <= N ; ++ i) {
        while( K > 0 && A[K+1] != A[i])
            K = Prefix[K];
        if(A[K+1] == A[i])
            ++ K;
        Prefix[i] = K;
    }
}

int main() {
    cin >> N;
    for(int i = 1 ; i <= N ; ++ i)
        cin >> A[i];
    for(int i = 2 ; i <= N ; ++ i)
        A[i-1] = A[i] - A[i-1];
    -- N;
    BuildPrefix();
    cout << N - Prefix[N] << '\n';
    for(int i = 1 ; i <= N - Prefix[N] ; ++ i)
        cout << A[i] << '\n';
    cin.close();
    cout.close();
    return 0;
}
