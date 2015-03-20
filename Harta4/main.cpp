#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "harta4.in";
const char outfile[] = "harta4.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 31;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, a[MAXN][MAXN], dp[MAXN][MAXN][MAXN][MAXN];

int memo(int i, int j, int n, int m) {
    if(dp[i][j][n][m])
        return dp[i][j][n][m];
    bool allTheSame = true;
    for(int x = i ; x <= n && allTheSame ; ++ x)
        for(int y = j ; y <= m && allTheSame ; ++ y)
            allTheSame &= (a[x][y] == a[i][j]);
    if(allTheSame) {
        dp[i][j][n][m] = 1;
        return dp[i][j][n][m]; /// return 1;
    }
    int ret = oo;
    for(int l = i ; l < n ; ++ l)
        ret = min(ret, 2 + memo(i, j, l, m) + memo(l + 1, j, n, m));
    for(int c = j ; c < m ; ++ c)
        ret = min(ret, 2 + memo(i, j, n, c) + memo(i, c + 1, n, m));
    dp[i][j][n][m] = ret;
    return ret;
}

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= M ; ++ j)
            fin >> a[i][j];
    fout << memo(1, 1, N, M) << '\n';
    fin.close();
    fout.close();
    return 0;
}
