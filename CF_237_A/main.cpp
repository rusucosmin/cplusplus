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

const int MAXN = 305;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N;
char a[MAXN][MAXN];

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> N;
    bool ok = true;
    for(int i = 1 ; i <= N && ok; ++ i) {
        cin >> (a[i] + 1);
        if(a[i][i] != a[1][1] || a[i][N - i + 1] != a[1][1]) {
            ok = false;
        }
    }
    if(a[1][1] == a[1][2])
        ok = false;
    for(int i = 1 ; i <= N && ok ; ++ i) {
        for(int j = 1 ; j <= N && ok ; ++ j) {
            if(i == j || j == N - i + 1)
                continue;
            if(a[i][j] != a[1][2])
                ok = false;
        }
    }
    if(ok)
        cout << "YES\n";
    else cout << "NO\n";
    fin.close();
    fout.close();
    return 0;
}
