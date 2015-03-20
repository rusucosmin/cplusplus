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

string file = "distincte";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 100005;
const int oo = (1<<31)-1;
const int MOD = 666013;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

pair<int, int> Query[MAXN];
int N, K, M, ind[MAXN], A[MAXN];
int Used[MAXN];
int aib[MAXN];
int Ans[MAXN];

struct ClassComp {
    inline bool operator () (const int &a, const int &b) const {
        return Query[a].second < Query[b].second;
    }
};

inline int lsb(int bit) {
    return (bit ^ (bit - 1)) & bit;
}

inline int mod(int val) {
    val = (val) % MOD;
    if(val < 0)
        val += MOD;
    return val;
}

inline void Update(int pos, int value) {
    for(int i = pos ; i <= N ; i += lsb(i)) {
        aib[i] = mod(aib[i] + value);
    }
}

inline int Question(int pos) {
    int sum = 0;
    for(int i = pos ; i > 0 ; i -= lsb(i)) {
        sum = mod(sum + aib[i]);
    }
    return sum;
}


int main() {
    cin >> N >> K >> M;
    for(int i = 1 ; i <= N ; ++ i)
        cin >> A[i];
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        cin >> x >> y;
        Query[i] = make_pair(x, y);
        ind[i] = i;
    }
    sort(ind + 1, ind + M + 1, ClassComp());
    for(int i = 1 ; i <= M ; ++ i) {
        for(int j = Query[ind[i-1]].second + 1 ; j <= Query[ind[i]].second ; ++ j) {
            if( Used[ A[j] ] )
                Update(Used[ A[j] ], (-1) * A[j]);
            Used[ A[j] ] = j;
            Update( j, A[j] );
        }
        Ans[ind[i]] = mod(Question(Query[ind[i]].second) - Question(Query[ind[i]].first - 1));
    }
    for(int i = 1 ; i <= M ; ++ i)
        cout << Ans[i] << '\n';
    cin.close();
    cout.close();
    return 0;
}
