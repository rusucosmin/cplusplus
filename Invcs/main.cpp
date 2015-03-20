#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "invcs.in";
const char outfile[] = "invcs.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 20;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, dp[1 << MAXN], s[MAXN];

int Memoization(int state) {
    if(dp[state] != -1)
        return dp[state];
    dp[state] = 0;
    int m = 0;
    for(int i = 0 ; i < N ; ++ i)
        if(state & ( 1 << i )) {
            if(m == s[i] - 1)
                dp[state] += Memoization(state ^ ( 1 << i ));
            if( m < s[i])
                m = s[i];
        }
    return dp[state];
}

int main() {
    fin >> N;
    for(int i = 1 ; i < ( 1 << N ) ; ++ i)
        dp[i] = -1;
    for(int i = 0 ; i < N ; ++ i) {
        fin >> s[i];
        if(s[i] == 1)
            dp[1 << i] = 1;
    }
    fout << Memoization(( 1 << N) - 1) << '\n';
    fin.close();
    fout.close();
    return 0;
}
