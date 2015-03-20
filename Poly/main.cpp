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

const char infile[] = "poly.in";
const char outfile[] = "poly.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 30005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

const int diviz[] = {2, 3, 7, 11, 19, 23, 37};
int N, dp[2][(1 << 8)];
short mask[MAXN];

inline short desc(const int &x) {
    short maskret = 0;
    for(int i = 0 ; i < 8 ; ++ i) {
        if(x % diviz[i] == 0)
            maskret |= (1 << i);
    }
    return maskret;
}

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        int x;
        fin >> x;
        mask[i] = desc(x);
        //dp[i][mask[i]] = 1;
    }
    for(int i = 1 ; i <= N ; ++ i) {
        for(int j = 0 ; j < (1 << 7) ; ++ j) {
            if(j == mask[i])
                dp[i & 1][j] = max(dp[i&1][j], 1);
            else dp[i&1][j] = max(dp[i&1][j], dp[i&1^1][j]);
            if((j & mask[i]) == 0)
                dp[i&1][mask[i]] = max(dp[i&1][mask[i]], dp[i&1^1][j] + 1);
        }
    }
    fout << *max_element(dp[N&1], dp[N&1] + (1 << 8)) << '\n';
    fin.close();
    fout.close();
    return 0;
}
