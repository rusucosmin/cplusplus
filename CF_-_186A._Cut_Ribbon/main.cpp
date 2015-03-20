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

const int MAXN = 4005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, A, B, C;
map<int, int> dp;

inline int Memo(int N) {
    if(N == 0)
        dp[N] = 0;
    if(N < 0)
        dp[N] = -oo;
    if(dp[N] != -1)
        return dp[N];
    return (dp[N] = (1 + max(max(Memo(N - A), Memo(N - B)), Memo(N - C))));
}

int main() {
    cin >> N >> A >> B >> C;
    for(int i = 0 ; i <= N ; ++ i)
        dp[i] = -1;
    cout << Memo(N) << '\n';
    fin.close();
    fout.close();
    return 0;
}
