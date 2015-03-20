#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "sarpe2.in";
const char outfile[] = "sarpe2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXV = 100005;
const int MAXN = 1005;
const int MOD = 666013;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, v[MAXV], A[MAXN][MAXN], dp[MAXN][MAXN];

const int dx[] = {0, 0, 1, -1, 1,-1, 1,-1};
const int dy[] = {1,-1, 0,  0, 1,-1,-1,1};

inline bool inside(const int &x, const int &y) {
    return x >= 1 && x <= N && y >= 1 && y <= N;
}

inline int Memoization(const int &x, const int &y) {
    if(dp[x][y] != -1)
        return dp[x][y];
    dp[x][y] = 0;
    for(int d = 0 ; d < 8 ; ++ d) {
        int newx = x + dx[d];
        int newy = y + dy[d];
        if(inside(newx, newy) && A[newx][newy] + 1 == A[x][y])
            dp[x][y] = (dp[x][y] + Memoization(newx, newy)) % MOD;
    }
    return dp[x][y];
}

int main() {
    fin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x;
        fin >> x;
        v[x] = i;
    }
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= N ; ++ j) {
            fin >> A[i][j];
            A[i][j] = v[A[i][j]];
            dp[i][j] = -1;
            if(A[i][j] == 1) {
                dp[i][j] = 1;
            }
        }
    int Ans = 0;
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= N ; ++ j)
            if(A[i][j] == M)
                Ans = ( Ans + Memoization(i, j) ) % MOD;
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
