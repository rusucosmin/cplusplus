#include <fstream>
#include <vector>
#include <bitset>
#include <string.h>

using namespace std;

const char infile[] = "stiva.in";
const char outfile[] = "stiva.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 505;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int dp[MAXN][MAXN], N;
char s[MAXN];

int main() {
    fin.getline(s, MAXN);
    N = strlen(s);
    for(int i = 0 ; i < N ; ++ i)
        dp[i][i] = 1;
    for(int d = 2 ; d <= N ; ++ d)
        for(int i = 0 ; i + d - 1 < N ; ++ i) {
            int j = i + d - 1;
            dp[i][j] = dp[i][j - 1] + 1;
            for(int t = i ; t < j ; ++ t)
                if(s[t] == s[j])
                    dp[i][j] = min(dp[i][j], dp[i][t] + dp[t + 1][j - 1]);
        }
    fout << dp[0][N - 1] * 2 + N << '\n';
    fin.close();
    fout.close();
    return 0;
}
