#include <fstream>
#include <vector>
#include <bitset>
#include <set>

using namespace std;

const char infile[] = "go.in";
const char outfile[] = "go.out";

ifstream cin(infile);
ofstream cout(outfile);

const int MAXN = 1005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct classComp {
    inline bool operator () (const int &a, const int &b) {
        return a > b;
    }
};

int N, M, a[MAXN][MAXN], nc, dp[MAXN][MAXN], Ans = -1, rx = 0 , ry = 0;
set< pair<int, int> > v;

const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};

inline bool inside(int a, int b) {
    if(0>a || 0>b || a>=N || b>=M) return 0;
    return 1;
}

void DFs(int x, int y) {
    a[x][y] = -1;
    ++ nc;
    for(int d = 0 ; d < 4 ; ++ d) {
        int xnou = x + dx[d];
        int ynou = y + dy[d];
        if(inside(xnou, ynou)) {
            if(a[xnou][ynou] == 0)
                v.insert(make_pair(xnou, ynou));
            if(a[xnou][ynou] == 2)
                DFs(xnou, ynou);
        }
    }
}

int main() {
    cin >> N >> M;
    for(int i = 0 ; i < N ; ++ i)
        for(int j = 0 ; j < M ; ++ j)
            cin >> a[i][j];
    for(int i = 0 ; i < N ; ++ i)
        for(int j = 0 ; j < M ; ++ j)
            if(2 == a[i][j]) {
                v.clear();
                nc = 0;
                DFs(i, j);
                if(v.size() == 1)
                    dp[v.begin()->first][v.begin()->second] += nc;
            }
    for(int i = 0 ; i < N ; ++ i)
        for(int j = 0 ; j < M ; ++ j)
            if(a[i][j] == 0)
                if(Ans < dp[i][j]) {
                    Ans = dp[i][j];
                    rx = i;
                    ry = j;
                }
    cout << rx << ' ' << ry << '\n';
    cin.close();
    cout.close();
    return 0;
}
