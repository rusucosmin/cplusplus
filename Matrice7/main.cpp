#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <string.h>

using namespace std;

const char infile[] = "matrice7.in";
const char outfile[] = "matrice7.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1005;
const int oo = 0x3f3f3f3f;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = { 0, 0, 1,-1};

int dp[MAXN][MAXN];
int N, M, xst, yst, xfn, yfn;
char a[MAXN][MAXN];
queue < pair<int, int> > Q;

inline int getNext(int x, int kick, int maxVal) {
    int ret = x + kick;
    if(ret >= maxVal)
        ret = 0;
    if(ret < 0)
        ret = maxVal - 1;
    return ret;
}

int main() {
    fin >> N >> M;
    fin.get();
    for(int i = 0 ; i < N ; ++ i)
        fin.getline(a[i], MAXN);
    fin >> xst >> yst >> xfn >> yfn;
    memset(dp, oo, sizeof(dp));
    Q.push(make_pair(xst, yst));
    dp[xst][yst] = 1;
    while(!Q.empty()) {
        int x = Q.front().first;
        int y = Q.front().second;
        if(x == xfn && yfn == y)
            break;
        Q.pop();
        for(int d = 0 ; d < 4 ; ++ d) {
            int newx = getNext(x, dx[d], N);
            int newy = getNext(y, dy[d], M);
            if(a[newx][newy] == '#')
                continue;
            if(dp[newx][newy] == oo) {
                dp[newx][newy] = dp[x][y] + 1;
                Q.push(make_pair(newx, newy));
            }
        }
    }
    fout << dp[xfn][yfn] << '\n';
    fin.close();
    fout.close();
    return 0;
}
