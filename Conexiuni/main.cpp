#include <fstream>
#include <vector>
#include <bitset>
#include <memory.h>

using namespace std;

const char infile[] = "conexiuni.in";
const char outfile[] = "conexiuni.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 5005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, dp[3][MAXN];
char a[MAXN], b[MAXN];
long long Ans;
int v[MAXN];

int main() {
    fin >> N >> M;
    fin.get();
    fin.getline(a + 1, MAXN);
    fin.getline(b + 1, MAXN);
    for(int i = 1 ; i <= N ; ++ i) {
        memset(v, 0, sizeof(v));
        memset(dp[i & 1], 0, sizeof(dp[i & 1]));
        for(int j = 1 ; j <= M ; ++ j)
            if(a[i] == b[j]) {
                dp[i & 1][j] = dp[(i & 1) ^ 1][j-1] + 1;
                ++ v[1];
                -- v[dp[i & 1][j] + 1];
            }
        for(int j = 1 ; j <= i ; ++ j) {
            v[j] += v[j-1];
            Ans += 1LL * (v[j]) ^ ( i + 1 ) ^ ( i - j + 1);
        }
    }
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
