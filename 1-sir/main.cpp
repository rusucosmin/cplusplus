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
#include <cmath>

using namespace std;

string file = "1-sir";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 100005;
const int oo = (1<<31);

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

int N, S, K, D[3][MAXN];

int main() {
    cin >> N >> S;
    K = N * (N - 1) / 2;
    if(fabs(S) > N * (N - 1) / 2) {
        cout << "0\n";
        return 0;
    }
    D[1][0] = 1;
    int P = 0;
    for(int i = 2 ; i <= N ; ++ i) {
        for(int j = 0 ; j < K ; ++ j) {
            D[P][j] = D[1-P][j+i-1] + D[1-P][abs(j - i + 1)];
            D[P][j] %= 194767;
        }
        P = 1 - P;
    }
    cout << D[1-P][S] << '\n';
    cin.close();
    cout.close();
    return 0;
}
