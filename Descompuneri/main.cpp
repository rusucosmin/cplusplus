#include <fstream>
#include <vector>
#include <bitset>
#include <map>
#include <algorithm>

using namespace std;

const char infile[] = "desc.in";
const char outfile[] = "desc.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 4005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

long long N, K, dp[MAXN][MAXN], dvz[MAXN], D;
map <long long, int> Hash;

inline void buildDivisors(const long long &N) {
    long long i;
    for(i = 1 ; 1LL * i * i < N ; ++ i)
        if(!(N % i)) {
            dvz[ ++ D ] = i;
            dvz[ ++ D ] = N / i;
        }
    if(1LL * i * i == N)
        dvz[ ++ D ] = i;
    sort(dvz + 1, dvz + D + 1);
    for(i = 1 ; i <= D ; ++ i)
        Hash[dvz[i]] = i;
}

void Write(const int &n, int k, int d) {
    if(n == 1)  return;
    while(dp[n][d] - dp[n][d + 1] < k) {
        k -= (dp[n][d] - dp[n][d + 1]);
        ++ d;
    }
    fout << dvz[d] << ' ';
    Write(Hash[dvz[n] / dvz[d]], k, d);
}

int main() {
    fin >> N >> K;
    buildDivisors(N);
    for(int i = 2 ; i <= D ; ++ i) {
        dp[i][i] = 1;
        for(int j = i - 1; j ; -- j) {
            dp[i][j] += dp[i][j + 1];
            if(!(dvz[i] % dvz[j]) && dvz[i] / dvz[j] >= dvz[j])
                dp[i][j] += dp[Hash[dvz[i] / dvz[j]]][j];
        }
    }
    fout << dp[D][2] << '\n';
    Write(D, K, 2);
    fin.close();
    fout.close();
    return 0;
}
