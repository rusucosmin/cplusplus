#include <fstream>
#include <vector>
#include <bitset>
#include <string.h>

using namespace std;

const char infile[] = "ratphu.in";
const char outfile[] = "ratphu.out";

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

int N, P;
long long dp[1 << MAXN][MAXN];
char S[MAXN];

int main() {
    fin >> S >> P;
    N = strlen(S);
    for(int i = 0 ; i < N ; ++ i) {
        S[i] = (S[i] - '0') % P;
        dp[1 << i][S[i]] = 1;
    }
    int MaxConf = (1 << N);
    for(int conf = 0 ; conf < MaxConf ; ++ conf) {
        if(!(conf & (conf - 1)))
            continue;
        for(int j = 0 ; j < N ; ++ j)
            if(conf & (1 << j)) {
                for(int k = 0 ; k < P ; ++ k)
                    dp[conf][(k * 10 + S[j])%P] += dp[conf ^ (1 << j)][k];
            }
    }
    fout << dp[MaxConf-1][0] << '\n';
    fin.close();
    fout.close();
    return 0;
}
