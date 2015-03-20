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

string file = "note";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXV = 520;
const int MAXN = 1030;
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

int V, N, M, P[MAXV][MAXN], S[MAXN], D[MAXN][MAXN];
bool is[MAXV][MAXN];

inline void Solve() {
	for(int i = 0; i <= MAXN; ++ i) D[i][0]=i;
	for(int i = 0; i <= MAXN; ++ i) D[0][i]=i;
    for(int i = 1 ; i <= M ; ++ i)
        for(int j = 1 ; j <= N ; ++ j)
            if(is[j][S[i]])
                D[i][j] = D[i-1][j-1];
                else D[i][j] = min(D[i-1][j] + 1, min(D[i-1][j-1] + 1, D[i][j-1] + 1));
    cout << D[M][N] << '\n';
}

int main() {
    cin >> V >> N;
    for(int i = 1 ; i <= V ; ++ i)
        for(int j = 1 ; j <= N ; ++ j)
            cin >> P[i][j], is[j][P[i][j]] = true;
    cin >> M;
    for(int i = 1 ; i <= M ; ++ i)
        cin >> S[i];
    Solve();
    cin.close();
    cout.close();
    return 0;
}
