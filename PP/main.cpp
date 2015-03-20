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
#include <unordered_map>

using namespace std;

const char infile[] = "pp.in";
const char outfile[] = "pp.out";

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

unordered_map<int, int> dp;
int N, K;


inline int Solve(int N) {
    if(dp[N])
        return dp[N];
    if(N == 0)
        return dp[N] = 2;
    dp[N] = 2;
    for(int i = 2 ; i <= K ; ++ i)
        if(Solve(N / i) == 2)
            dp[N] = 1;
    return dp[N];
}

int main() {
    fin >> N >> K;
    fout << 2 - Solve(N) << '\n';
    fin.close();
    fout.close();
    return 0;
}
