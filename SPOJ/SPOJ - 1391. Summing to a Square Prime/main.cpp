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

const int MAXN = 505;
const int oo = 0x3f3f3f3f;
const int MAXV = 8000;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

bitset <MAXV> notPrime, isSquare;
int sp2[MAXN], N;

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    for(int i = 1 ; i * i < MAXV ; ++ i)
        isSquare[i * i] = 1;
    for(int i = 2 ; i < MAXV ; ++ i)
        if(!notPrime[i]) {
            for(int j = i + i ; j < MAXV ; j += i)
                notPrime[j] = true;
            bool check = false;
            for(int j = 1 ; j * j <= i && !check ; ++ j)
                if(isSquare[i - j * j])
                    check = true;
            if(check)
                sp2[++ N] = i,
                cerr << i << ' ';
        }
    int t, n, k;
    cin >> t;
    while(t --) {
        int n, k;
        cin >> n >> k;

    }
    fin.close();
    fout.close();
    return 0;
}
