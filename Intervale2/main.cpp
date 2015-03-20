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

string file = "intervale2";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 100005;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, A[MAXN], P[MAXN], ind[MAXN], Ans[MAXN], aib[MAXN];

struct ClassComp {
    inline bool operator () (const int &a, const int &b) const {
        return (A[a] > A[b] || (A[a] == A[b] && a > b));
    }
};


inline int lsb(int bit) {
    return (bit ^ (bit - 1) & bit);
}

inline void Insert(int Pos) {
    for(int i = Pos ; i <= N ; i += lsb(i))
        ++ aib[i];
}

inline int Query(int Pos) {
    int Answ = 0;
    for(int i = Pos ; i > 0 ; i -= lsb(i))
        Answ += aib[i];
    return Answ;
}

int main() {
    cin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        cin >> A[i];
        ind[i] = i;
    }
    for(int i = 1 ; i <= N ; ++ i)
        cin >> P[i];
    sort(ind + 1, ind + N + 1, ClassComp());
    for(int i = 1 ; i <= N ; ++ i) {
        int x = P[ind[i]];
        int y = ind[i];
        Ans[y] = Query(y) - Query(x-1);
        Insert(ind[i]);
    }
    for(int i = 1 ; i <= N ; ++ i)
        cout << Ans[i] << ' ';
    cin.close();
    cout.close();
    return 0;
}
