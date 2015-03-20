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

string file = "culori";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 600;
const int MOD = 9901;
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

int C[MAXN], D[2*MAXN][2*MAXN], N;

int main() {
    cin >> N;
    N = 2*N - 1;
    for(int i = 1 ; i <= N ; ++ i) {
        cin >> C[i];
        D[i][i] = 1;
    }
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= N ; ++ j)
            if(C[i + j] == C[j])
                for(int k = j + 1 ; k <= i + j ; ++ k) {
                    D[j][j+i] = D[j][j+i] + D[j+1][k] * D[k+1][j + i];
                    D[j][j+i] %= MOD;
                }
    cout << D[1][N] << '\n';
    cin.close();
    cout.close();
    return 0;
}
