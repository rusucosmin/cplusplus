/**
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

string file = "joc13";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 5005;
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

int A[3][MAXN], B[3][MAXN][12], N, M, K;

int main() {
    cin >> N >> K;
    for(int i = 1 ; i <= 2 ; ++ i)
        for(int j = 1 ; j <= N ; ++ j)
            cin >> A[i][j];
    B[1][1][1] = A[1][1];
    B[2][1][1] = A[1][1] + A[2][1];
    for(int j = 2 ; j <= N ; ++ j) {
        for(int i = 1 ; i <= 2 ; ++ i)
            for(int q = 2 ; q <= K ; ++ q) {
                    if(q > j)
                        break;
                    B[i][j][q] = B[i][j-1][q-1] + A[i][j];
            }
        for(int i = 1 ; i <= 2 ; ++ i) {
            int maxi = -(1<<31)+1;
            for(int q = 2 ; q <= K ; ++ q) {
                if(q > j)
                    break;
                maxi = max(maxi, B[3 - i][j][q]);
            }
            B[i][j][1] = maxi + A[i][j];
        }
    }
    int Sol = -oo;
    for(int i = 1 ; i <= K ; ++ i)
        Sol = max(Sol, B[2][N][i]);
    cout << Sol << '\n';
    cin.close();
    cout.close();
    return 0;
}
*/
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

string file = "joc13";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 5005;
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

int A[3][MAXN], D[3][MAXN], N, M, K;

int main() {
    cin >> N >> K;
    for(int i = 1 ; i <= 2 ; ++ i)
        for(int j = 1 ; j <= N ; ++ j)
            cin >> A[i][j];
    D[1][1] = A[1][1];
    for(int j = 2 ; j <= N ; ++ j)
        for(int i = 1 ; i <= 2 ; ++ i) {
            int actMax = -oo;
            int Sum = A[i][j];
            for(int i1 = 1 ; i1 < K && i1 < j ; ++ i1) {
                Sum += A[i][j - i1];
                if(Sum + D[3-i][j - i1] > actMax)
                    actMax = Sum + D[3 - i][j - i1];
            }
            D[i][j] = actMax;
        }
    cout << max(D[2][N], D[1][N] + A[2][N]);
    cin.close();
    cout.close();
    return 0;
}
