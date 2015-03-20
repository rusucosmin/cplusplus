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

string file = "ec";

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

vector <int> ec;
char * pch;
char s[100];
int N, M;
bitset<25000> us;
int eqs1, eqs2, tab1, tab2;

inline void Solve() {
    if(ec.size() == 3) {
        int a = ec[0];
        int b = ec[1];
        int c = ec[2];

        ++ eqs1;

        /// ax + b = c
        /// ax = c - b
        /// x = (c - b) / a
        if(!a)
            return;
        if( ((c - b) % a == 0))
            if(us[ (c-b)/a + 10000 ])
                ++ tab1;
    }
    if(ec.size() == 5) {
        int a = ec[0];
        int b = ec[2];
        int c = ec[3] - ec[4];
        ++ eqs2;
        /// ax^2 + bx + c - d = 0;
        /// ax + b = c
        /// ax = c - b
        /// x = (c - b) / a
        /// bx + c = d;
        /// bx + c = 0;
        int delta = b * b - 4 * a * c;
        int rad = sqrt(delta);
        if(!a) { // handle
            if( ( c % b == 0))
            if(us[ (c)/b + 10000 ])
                ++ tab2;
            return;
        }
        if(rad * rad == delta && delta >= 0 && a) {
            bool ok1 = false, ok2 = false;
            if( (-b + rad) % (2 * a) == 0) {
                int x1 = (-b + rad) / (2 * a);
                if(us[x1 + 10000]) {
                    ok1 = true;
                }
            }
            if( (-b - rad) % (2 * a) == 0 ) {
                int x2 = (-b - rad) / (2 * a);
                if(us[x2 + 10000]) {
                    ok2 = true;
                }
            }
            if(ok1 && ok2)
                ++ tab2;
        }
    }
}

int main() {
    cin >> N >> M;
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= N ; ++ j) {
            int x;
            cin >> x;
            us[x + 10000] = 1;
        }
    cin.get();
    char d[] = "+x=^";
    for(int i = 1 ; i <= M ; ++ i) {
        ec.clear();
        cin.getline(s, 100);
        pch = strtok(s, d);
        while(pch != NULL) {
            ec.push_back(atoi(pch));
            pch = strtok(NULL, d);
        }
        Solve();
    }
    cout << eqs1 << ' ' << tab1 << '\n' << eqs2 << ' ' << tab2 << '\n';
    cin.close();
    cout.close();
    return 0;
}
