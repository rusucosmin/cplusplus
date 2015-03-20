#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "biti3.in";
const char outfile[] = "biti3.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1670;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, dp[MAXN][MAXN];

/// dp[i][j] = numarul de biti de lungime de i cu exact j biti de 1

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= N ; ++ i) {
        dp[i][0] = 1;
        for(int j = 1 ; j <= N ; ++ j)
            if(j > i)  dp[i][j] = 0;
            else  dp[i][j] = dp[i-1][j] + dp[i-1][j-1];
    }
    int bitCount = 3;
    for(int i = N ; i ; -- i)
        if(dp[i][bitCount] >= M)  fout << "0";
        else fout << "1", M = M - dp[i][bitCount], -- bitCount;
    fin.close();
    fout.close();
    return 0;
}
