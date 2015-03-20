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

string file = "cutii";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 3505;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct bo{
    int x, y, z;
} box[MAXN];

struct ClassComp {
    inline bool operator () (const bo &a, const bo &b) const {
        return a.z < b.z;
    }
};

int N, T, Ans;
int aib[MAXN][MAXN];

inline int lsb(int bit) {
    return (bit ^ (bit - 1) & bit);
    /// sau bit & -bit;
}

inline void Update(int x, int y, int value) {
    for(int i = x ; i <= N ; i += lsb(i))
        for(int j = y ; j <= N ; j += lsb(j))
            aib[i][j] = max(aib[i][j], value);
}

inline void clearAib(int x, int y) {
    for(int i = x ; i <= N ; i += lsb(i))
        for(int j = y ; j <= N ; j += lsb(j))
            aib[i][j] = 0;
}

inline int Query(int x, int y) {
    int ret = 0;
    for(int i = x ; i > 0 ; i -= lsb(i))
        for(int j = y ; j > 0 ; j -= lsb(j))
            ret = max(aib[i][j], ret);
    return ret;
}

inline void Read() {
    for(int i = 1 ; i <= N ; ++ i)
        cin >> box[i].x >> box[i].y >> box[i].z;
}

inline void Solve() {
    sort(box + 1, box + N + 1, ClassComp());
    for(int i = 1 ; i <= N ; ++ i) {
        int actMax = Query(box[i].x - 1, box[i].y - 1) + 1;
        Update(box[i].x , box[i].y, actMax);
        Ans = max(Ans, actMax);
    }
    cout << Ans << '\n';
}

inline void Clear() {
    for(int i = 1 ; i <= N ; ++ i)
        clearAib(box[i].x, box[i].y);
    Ans = 0;
}

int main() {
    for(cin >> N >> T ; T ; -- T) {
        Read();
        Solve();
        Clear();
    }
    cin.close();
    cout.close();
    return 0;
}
