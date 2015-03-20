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

string file = "password";

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

struct ClassComp {
    inline bool operator () (const int &a, const int &b) const {
        return a > b;
    }
};

char s[MAXN];
vector<int> L;

int main() {
    cin >> s;
    int N = strlen(s);
    int min = 0, p = 1, l = 0;
    while( (p < N) and (min+l+1 < N)) {
        if( s[min+l] == s[(p+l) % N] ) l = l+1;
        if( s[min+l] < s[(p+l) % N] ) p = p+l+1, l = 0;
        if( s[min+l] > s[(p+l) % N] ) min = max(min+l+1, p), p = min + 1, l = 0;
    }
    cout << min << '\n';
    cin.close();
    cout.close();
    return 0;
}
