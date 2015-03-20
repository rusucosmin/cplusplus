#include <fstream>
#include <vector>
#include <string.h>
#include <bitset>
#include <algorithm>

using namespace std;

const char infile[] = "sant.in";
const char outfile[] = "sant.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 105;
const int MAXS = 1005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int S, N, C, L[MAXN], P[MAXN], dp[3][MAXS], previ[MAXN][MAXS];
vector <int> Ans;

void Write(int n, int s) {
    if(n) {
        Ans.push_back(previ[n][s]);
        Write(n - 1, s - L[previ[n][s]]);
    }
}

int main() {
    fin >> S >> N >> C;
    memset(dp, oo, sizeof(dp));
    for(int i = 1 ; i <= C ; ++ i) {
        int x, y;
        fin >> x >> y;
        L[i] = x;
        P[i] = y;
        if(dp[1&1][x] > y) {
            dp[1&1][x] = y;
            previ[1][x] = i;
        }
    }
    for(int i = 2; i <= N ; ++ i) {
        for(int j = 1 ; j <= S ; ++ j) {
            for(int k = 1 ; k <= C ; ++ k) {
                if(j - L[k] > 0) {
                    if(dp[(i&1)][j] > dp[(i&1)^1][j - L[k]] + P[k]) {
                        dp[(i&1)][j] = dp[(i&1)^1][j - L[k]] + P[k];
                        previ[i][j] = k;
                    }
                }
            }
        }
        for(int j = 1 ; j <= S; ++ j)
            dp[i&1^1][j] = oo;
    }
    if(dp[N&1][S] == oo) {
        fout << "0\n";
        return 0;
    }
    fout << dp[N&1][S] << '\n';
    Write(N, S);
    sort(Ans.begin(), Ans.end());
    for(int i = 0 ; i < Ans.size() ; ++ i)
        fout << Ans[i] << ' ';
    fin.close();
    fout.close();
    return 0;
}
