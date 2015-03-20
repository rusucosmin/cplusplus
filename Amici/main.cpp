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

string file = "amici";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 1005;
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

bool G[MAXN][MAXN];
int T, N, M, Cycle[MAXN];

inline int searchEdge(int x, int y) {
    for(int i = 1 ; i <= N ; ++ i)
        if( G[ x ][ Cycle[i] ] && G[ y ][ Cycle[i+1] ])
            return i;
}

inline void Read() {
    /// initialize()
    memset(G, 1, sizeof(G));
    /// read()
    cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[x][y] = 0;
        //G[y][x] = 0;
    }
}

inline void Rotates(int a, int b) {
    while(a < b) {
        swap(Cycle[a], Cycle[b]);
        ++ a, -- b;
    }
}

inline void Solve() {
    for(int i = 1 ; i <= N ; ++ i)
        Cycle[i] = i;
    Cycle[N+1] = 1;
    for(int i = 1 ; i <= N ; ++ i)
        if( !G[ Cycle[i] ][ Cycle[i+1] ] ) {
            int X = searchEdge(Cycle[i], Cycle[i+1]);
            cout << X << ' ' << i << '\n';
            Rotates(min(i, X) + 1, max(i, X));
        }
}

inline void Write() {
    for(int i = 2 ; i <= N + 1 ; ++ i)
        cout << Cycle[i] << ' ';
    cout << '\n';
}

int main() {
    for(cin >> T ; T ; -- T) {
        Read();
        Solve();
        Write();
    }
    cin.close();
    cout.close();
    return 0;
}
