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

const char infile[] = "elmaj.in";
const char outfile[] = "elmaj.out";

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

int n, a[MAXN], elmaj, k;

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    fin >> n;
    for(int i = 1 ; i <= n ; i ++)
        fin >> a[i];
    elmaj = -1;
    for(int i = 1 ; i <= n ; i ++)
        if(k == 0) {
            elmaj = a[i];
            k = 1;
        }
        else if(a[i] == elmaj)
            ++ k;
        else
            -- k;
    if(elmaj == -1) {
        fout << elmaj;
        return 0;
    }
    k = 0;
    for(int i = 1 ; i <= n ; i ++ )
        if(elmaj == a[i])
             ++ k;
    if(k < n / 2 + 1) {
        fout << -1;
        return 0;
    }
    fout << elmaj << ' ' << k << '\n';
    fin.close();
    fout.close();
    return 0;
}
