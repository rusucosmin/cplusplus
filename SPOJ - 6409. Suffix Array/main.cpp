#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>

using namespace std;

const char infile[] = "input.in";
const char outfile[] = "output.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct entry {
    int p, nr[2];
} L[MAXN];

string s;
int P[25][MAXN];
int ind[MAXN];

struct classComp {
    inline bool operator () (const entry &a, const entry &b) const {
        return a.nr[0] < b.nr[0] && (a.nr[0] == b.nr[0] && a.nr[1] < b.nr[1]);
    }
};

struct comp {
    inline bool operator () (const int &a, const int &b) const {
        return s[a] < s[b];
    }
};



int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    getline(cin, s);

    for(int i = 0 ; i < s.size() ; ++ i)
        P[0][i] = s[i];
    cerr << s << '\n';
    int stp, k;
    for(stp = 1, k = 1 ; (k >> 1) < s.size() ; k <<= 1, ++ stp) {
        for(int i = 0 ; i < s.size() ; ++ i) {
            L[i].p = i;
            L[i].nr[0] = P[stp - 1][i];
            L[i].nr[1] = i + k < s.size() ? P[stp - 1][i + k] : -1;
        }
        sort(L, L + s.size(), classComp());
        for(int i = 0 ; i < s.size() ; ++ i)
            P[stp][L[i].p] = i > 0 && L[i].nr[0] == L[i - 1].nr[0] && L[i].nr[1] == L[i - 1].nr[1] ? P[stp][L[i - 1].p] : i;
    }
    for(int i = 0 ; i < s.size() ; ++ i)
        cout << P[stp - 1][i] << '\n';
    cout << "\n\n\n";
    for(int i = 0 ; i < s.size() ; ++ i)
        cout << L[i].p << '\n';
    return 0;
}
