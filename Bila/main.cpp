#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <cstring>
#include <string>
#include <stack>
#include <deque>
#include <iomanip>
#include <set>
#include <map>
#include <cassert>
#include <ctime>
#include <list>
#include <iomanip>

using namespace std;

string file = "bila";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 135;
const int oo = 0x3f3f3f3f;
const int dx[] = {1 , 0, -1,  0};
const int dy[] = {0,  1,  0, -1};

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct ClassComp {
    inline bool operator () (const pair<int, int> &a, const pair<int, int> &b) const {
        return a.first < b.first || (a.first == b.first && a.second > b.second);
    }
};

int N, M, A[MAXN][MAXN], D[MAXN][MAXN];
pair<int, int> Ans;

void Fill(int x, int y) {
    int xmin, ymin, minval = oo;
    for(int d = 0 ; d < 4 ; ++ d) {
        int xnou = x + dx[d];
        int ynou = y + dy[d];
        if(xnou >= 1 && xnou <= N && ynou >= 1 && ynou <= M)
            if(minval > A[xnou][ynou]) {
                minval = A[xnou][ynou];
                xmin = xnou;
                ymin = ynou;
            }
    }
    if(minval < A[x][y]) { /// conditia de rostogolire
        if(!D[xmin][ymin]) {
            Fill(xmin, ymin);
            D[x][y] = D[xmin][ymin] + 1;
        }
        else D[x][y] = D[xmin][ymin] + 1;
    }
    else D[x][y] = 1;
    Ans = max(Ans, make_pair(D[x][y], A[x][y]), ClassComp());
}

int main() {
    cin >> N >> M;
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= M ; ++ j)
            cin >> A[i][j];
    for(int i = 1 ; i <= N ;  ++ i)
        for(int j = 1 ; j <= M ; ++ j)
            //if(!D[i][j]) {
                Fill(i, j);
            //}
    cout << Ans.first << ' ' << Ans.second << '\n';
    cin.close();
    cout.close();
    return 0;
}
