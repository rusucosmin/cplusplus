#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "cabana.in";
const char outfile[] = "cabana.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 4005;
const int MAXK = 1000005;
const int oo = 0x3f3f3f3f;
const int MOD = 1000000007;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int fact[MAXK];

int lgPut(const long long &A, const long long &N) {
    if(N == 1)
        return (1LL*A) % MOD;
    long long Square = (1LL * A * A) % MOD;
    if(N % 2)
        return (A * 1LL * lgPut(Square, (N - 1 )/ 2)) % MOD;
    return lgPut(Square, N / 2);
}

int main() {
    fact[0] = fact[1] = 1;
    for(int i = 2 ; i < MAXK ; ++ i)
        fact[i] = (1LL * fact[i - 1] * i) % MOD;
    int T;
    fin >> T;
    for(int test = 1 ;test <= T ; ++ test) {
        long long N, K;
        fin >> N >> K;
        int Ans1 = lgPut(1LL*fact[K], N / K + 1);
        int Ans2 = lgPut(1LL*fact[K - N % K], 1LL*(MOD - 2));
        fout << (1LL * Ans1 * Ans2) % MOD << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
