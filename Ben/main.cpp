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

string file = "ben";

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
    inline bool operator () (const pair<int, int> &a, const pair<int, int> &b) const {
        return (a.second > b.second) || (a.second == b.second && a.first < b.first);
    }
};

int N, Ans;
pair<int, int> A[MAXN];

int main() {
    cin >> N;
    for(int i = 1 ; i <= N ; ++ i)
        cin >> A[i].first >> A[i].second;
    sort(A+1, A+N+1, ClassComp());
    int X = 0x3f3f3f3f;
    for(int i = 1 ; i <= N ; ++ i)
        if(A[i].second < X) {
            X = A[i].first;
            ++ Ans;
        }
    cout << Ans << ' ' << 12 << '\n';
    cin.close();
    cout.close();
    return 0;
}
