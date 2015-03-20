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

const char infile[] = "palin3.in";
const char outfile[] = "palin3.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 105;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

bool dp[MAXN][MAXN];
char s[MAXN];

inline bool eliminated(const int &i, const int &j) {
    if(i > j)
        return true;
    return dp[i][j];
}

bool solve(string s, const int &N) {
    for(int i = 0 ; i < N ; ++ i)
        for(int j = 0 ; j < N ; ++ j)
            dp[i][j] = 0;
    for(int i = 1 ; i + 1 < N ; ++ i)
        if(s[i-1] == s[i+1])
            dp[i-1][i+1] = 1;
    for(int len = 3 ; len < N ; ++ len)
        for(int i = 0 ; i + len < N ; ++ i) {
            int j = i + len;
            for(int k = i + 1 ; k <= j ; ++ k) {
                if(eliminated(i, k - 1) && eliminated(k, j))
                    dp[i][j] = 1;
                if(s[i] == s[j] && eliminated(i + 1, k - 1) && eliminated(k + 1, j - 1))
                    dp[i][j] = 1;
            }
        }
    return dp[0][N-1];
}

int main() {
    int T;
    fin >> T;
    while(T -- ) {
        string s;
        fin >> s;
        int N = s.size();
        bool Ans = solve(s, N);
        if(Ans == 1)
            fout << "DA\n";
        else fout << "NU\n";
    }
    fin.close();
    fout.close();
    return 0;
}
