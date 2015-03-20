#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "ccm.in";
const char outfile[] = "ccm.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 17;
const int MOD = 9901;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int L, R, M, dp[MAXN][(1 << MAXN)] = {1};
bitset <MAXN> G[MAXN];

inline int bitCount(int conf) {
    int ret = 0;
    while(conf) {
        ++ ret;
        conf &= (conf - 1);
    }
    return ret;
}

int main() {
    fin >> L >> R >> M;
    for(int i = 0 ; i < M ; ++ i) {
        int x, y;
        fin >> x >> y;
        G[x][y] = true;
    }
    int maxConf = (1 << R);
    for(int i = 1 ; i <= L ; ++ i)
        for(int conf = 0 ; conf < maxConf ; ++ conf) {
            dp[i][conf] = dp[i-1][conf];
            for(int j = 1 ; j <= R ; ++ j)
                if(G[i][j] && ((1 << (j - 1)) & conf))
                    dp[i][conf] = (dp[i][conf] + dp[i - 1][conf ^ (1 << ( j - 1 ))]) % MOD;
        }
    int ccm = 0, ccmnr = 0;
    for(int conf = maxConf - 1 ; conf > 0 ; -- conf)
        if(dp[L][conf]) {
            ccm = bitCount(conf);
            break;
        }
    for(int conf = 0 ; conf < maxConf ; ++ conf) {
        if(bitCount(conf) == ccm)
            ccmnr = (ccmnr + dp[L][conf]) % MOD;
    }
    fout << ccm << ' ' << ccmnr << '\n';
    fin.close();
    fout.close();
    return 0;
}
