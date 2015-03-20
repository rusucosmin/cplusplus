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

const char infile[] = "antobroasca.in";
const char outfile[] = "antobroasca.out";

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

inline int gcd(int a, int b) {
    if(!b)
        return a;
    return gcd(b, a % b);
}

inline bool euclid(int c, int a, int b) {
    if(c % __gcd(a, b) == 0)
        return 1;
    return 0;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    int T, X, Y, Z, A, B;
    fin >> T;
    cerr << gcd(-200, 100) << ' ' << __gcd(-200, 100);
    while(T--) {
        fin >> X >> Y >> Z >> A >> B;
        if(euclid(A, X, Z) && euclid(B, Y, Z) && euclid(A - B, X, -Y))
            fout << "DA\n";
        else
            fout << "NU\n";
    }
    fin.close();
    fout.close();
    return 0;
}
