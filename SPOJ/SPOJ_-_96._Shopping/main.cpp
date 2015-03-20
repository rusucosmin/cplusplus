#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cassert>

using namespace std;

const char infile[] = "input.in";
const char outfile[] = "output.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 50;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M;
char a[MAXN][MAXN];
int dp[MAXN][MAXN];
pair<int, int> st, fn;

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0,  0,-1, 1};

inline int BFs() {
    memset(dp, 0x3f, sizeof(dp));
    dp[st.first][st.second] = 0;
    queue <pair<int, int> > Q;
    Q.push(st);
    while(!Q.empty()) {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();
        for(int d = 0 ; d < 4 ; ++ d) {
            int xnou = x + dx[d];
            int ynou = y + dy[d];
            if(xnou >= 1 && xnou <= N && ynou >= 1 && ynou <= M) {
                if(a[xnou][ynou] != 'X' && dp[xnou][ynou] > dp[x][y] + (a[xnou][ynou] - '0') * (a[xnou][ynou] != 'D')) {
                    dp[xnou][ynou] = dp[x][y] + (a[xnou][ynou] - '0') * (a[xnou][ynou] != 'D');
                    Q.push(make_pair(xnou, ynou));
                }
            }
        }
    }
    return dp[fn.first][fn.second];
}

int main() {
    while(scanf("%d%d", &N, &M) == 2) {
        if(!N && !M)
            return 0;
        swap(N, M);
        for(int i = 1 ; i <= N ; ++ i) {
            scanf(" %s", a[i] + 1);
            for(int j = 1 ; j <= M ; ++ j)
                if(a[i][j] == 'S')
                    st = make_pair(i, j);
                else if(a[i][j] == 'D')
                    fn = make_pair(i, j);
        }
        int Ans = BFs();
        assert(Ans != oo);
        printf("%d\n", Ans);
    }
    fin.close();
    fout.close();
    return 0;
}
