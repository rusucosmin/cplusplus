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

string file = "permsplit";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 1000005;
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

struct Int {
    int li, ls, poz;
};

Int Stack[MAXN];
int N, Top;
vector<int> Sol;

inline bool Unite() {
    if(Stack[Top-1].ls + 1 == Stack[Top].li) {
        Stack[Top-1].ls = Stack[Top].ls;
        Sol.push_back(Stack[Top-1].poz);
        Stack[Top-1].poz = Stack[Top].poz;
        -- Top;
        return true;
    }
    else if ( Stack[Top].ls + 1 == Stack[Top-1].li) {
        Stack[Top-1].li = Stack[Top].li;
        Sol.push_back(Stack[Top-1].poz);
        Stack[Top-1].poz = Stack[Top].poz;
        -- Top;
        return true;
    }
    return false;
}


int main() {
    cin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        int x;
        cin >> x;
        Stack[++Top].li = x;
        Stack[Top].poz = i;
        Stack[Top].ls = x;
        while( Top > 1 && Unite() );
    }
    if( Top != 1 )
        cout << -1 << '\n';
    else
    for(vector<int> :: reverse_iterator it = Sol.rbegin() ; it != Sol.rend() ; ++ it)
        cout << *it << ' ';
    cin.close();
    cout.close();
    return 0;
}
