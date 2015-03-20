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

const char infile[] = "permlcs.in";
const char outfile[] = "permlcs.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int MAXM = 15;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, dp[MAXN], a[MAXM][MAXN], where[MAXM][MAXN];

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i)
        for(int j = 1 ; j <= N ; ++ j) {
            fin >> a[i][j];
            where[i][a[i][j]] = j;
        }
    for(int i = 1 ; i <= N ; ++ i) {
        for(int j = 1 ; j < i ; ++ j) {
            int x = a[1][i];
            int y = a[1][j];
            bool okay = true;
            for(int k = 2 ; k <= M ; ++ k)
                if(where[k][x] < where[k][y])
                     okay = false;
            if(okay)
                dp[i] = max(dp[i], dp[j] + 1);
        }
    }
    fout << *max_element(dp + 1, dp + N + 1) + 1 << '\n';
    fin.close();
    fout.close();
    return 0;
}
