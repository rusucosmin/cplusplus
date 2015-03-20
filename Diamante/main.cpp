#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "diamant.in";
const char outfile[] = "diamant.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXS = 100010;
const int MOD = 10000;
const int oo = 0x3f3f3f3f;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

inline int myAbs(int value) {
    if(value <= 0)
        return value * -1;
    return value;
}

int N, M, X, dp[2][MAXS], last = 0, act = 1;

int main() {
    fin >> N >> M >> X;
    dp[0][0] = 1;
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= M ; ++ j) {
            for(int k = 0 ; k < MAXS ; ++ k)
                dp[act][k] = (dp[last][myAbs(k - i * j)] + dp[last][k] + dp[last][k + i * j]) % MOD;
            last ^= 1;
            act ^= 1;
        }
    if(myAbs(X) >= MAXS)
        fout << "0\n";
    else
        fout << dp[last][myAbs(X)] << '\n';
    fin.close();
    fout.close();
    return 0;
}
