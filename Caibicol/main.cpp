#include <fstream>
#include <vector>
#include <bitset>
#include <memory.h>

using namespace std;

const char infile[] = "caibicol.in";
const char outfile[] = "caibicol.out";

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

int N, K, nrb, nrw, s[MAXN];
int dp[MAXN][MAXN]; /// costul minim de a pune caii din intervalul [1, i], in j grajduri

int main() {
    fin >> N >> K;
    memset(dp, oo, sizeof(dp));
    for(int i = 1 ; i <= N ; ++ i) {
        bool tip;
        fin >> tip;
        if(tip)
            ++ nrb;
        else ++ nrw;
        s[i] = s[i-1] + tip;
        dp[i][1] = nrb * nrw;
    }
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 2 ; j <= K ; ++ j)
            for(int k = j - 1 ; k < i ; ++ k) {
                nrb = s[i] - s[k];
                nrw = i - k - nrb;
                dp[i][j] = min(dp[i][j], dp[k][j - 1] + nrb * nrw);
            }
    fout << dp[N][K] << '\n';
    fin.close();
    fout.close();
    return 0;
}
