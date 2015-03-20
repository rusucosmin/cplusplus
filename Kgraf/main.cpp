#include <fstream>
#include <vector>
#include <bitset>
#include <memory.h>

using namespace std;

const char infile[] = "kgraf.in";
const char outfile[] = "kgraf.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXM = 905;
const int MAXN = 305;
const int oo = 0x3f3f3f3f;

typedef vector< pair<int, int> > Graph[MAXN];
typedef vector< pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;
bitset <MAXN> Used;
int dp[MAXN][MAXM][MAXM];
int N, M, K;
int Ans = -oo;

void DFs(const int &Node) {
    Used[Node] = 1;
    memset(dp[Node], -oo, sizeof(dp[Node]));
    dp[Node][0][0] = 0;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(!Used[it->first])
            DFs(it->first);
        for(int i = 0 ; i <= K ; ++ i)
            for(int j = 0 ; j <= K ; ++ j) {
                if(i > 0) {
                    dp[Node][i][j] = max(dp[Node][i][j], dp[it->first][i - 1][j] + it->second);
                    if(j > 0)
                        dp[Node][i][j] = max(dp[it->first][i - 1][j - 1], dp[Node][i][j]);
                }
                if(j > 0)
                    dp[Node][i][j] = max(dp[Node][i][j], dp[it->first][i][j - 1] - it->second);
                dp[Node][i][j] = max(dp[Node][i][j], dp[it->first][i][j]);
            }
    }
    Ans = max(Ans, dp[Node][K][K]);
}

int main() {
    fin >> N >> M >> K;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        fin >> x >> y >> z;
        G[x].push_back(make_pair(y, z));
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(!Used[i])
            DFs(i);
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}














































































































