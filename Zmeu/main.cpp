#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <string.h>

using namespace std;

const char infile[] = "zmeu.in";
const char outfile[] = "zmeu.out";

ifstream cin(infile);
ofstream cout(outfile);

const int MAXN = 105;
const int MAXP = 500;
const int oo = 0x3f3f3f3f;
const int dx[] = {0, 0, -1, 1};
const int dy[] = {1,-1,  0, 0};

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, P, a[MAXN][MAXN], b[MAXN][MAXN], dp[MAXN][MAXN][MAXP];

struct type {
    int x, y, z;
    type() {
        x = y = z = 0;
    }
    type(int _x, int _y, int _z) {
        x = _x;
        y = _y;
        z = _z;
    }
};

inline bool inside(const int &x, const int &y) {
    return x >= 1 && x <= N && y >= 1 && y <= N;
}

inline void BellmanFord() {
    /// dp[i][j][P] = costul minim de a junge in (i, j) cu pericolul P
    queue <type> Q;
    Q.push(type(1, 1, 0));
    memset(dp, oo, sizeof(dp));
    dp[1][1][0] = 0;
    while(!Q.empty()) {
        int x = Q.front().x;
        int y = Q.front().y;
        int z = Q.front().z;
        Q.pop();
        for(int d = 0 ; d < 4 ; ++ d) {
            int newx = x + dx[d];
            int newy = y + dy[d];
            if(inside(newx, newy)) {
                if(z + a[newx][newy] <= P) {
                    if(dp[newx][newy][z + a[newx][newy]] > dp[x][y][z]) {
                        dp[newx][newy][z + a[newx][newy]] = dp[x][y][z];
                        Q.push(type(newx, newy, z + a[newx][newy]));
                    }
                }
                if(dp[newx][newy][z] > dp[x][y][z] + b[newx][newy]) {
                    dp[newx][newy][z] > dp[x][y][z] + b[newx][newy];
                    Q.push(type(newx, newy, z));
                }
            }
        }
    }
    int Ans = oo;
    for(int i = 0 ; i <= P ; ++ i)
        Ans = min(Ans, dp[N][N][i]);
    cout << Ans << '\n';
}

int main() {
    cin >> N >> P;
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= N ; ++ j)
            cin >> a[i][j];
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= N ; ++ j)
            cin >> b[i][j];
    BellmanFord();
    cin.close();
    cout.close();
    return 0;
}
