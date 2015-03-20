#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

ifstream fin("betasah.in");
ofstream fout("betasah.out");

const int maxn = 1005;
const int maxd = 105;
const int maxk = 55;

pair<int, int> queen[maxd];
bitset <maxn> used[maxn], check[maxn];
int n, d, k;

const int dx[] = {0,1,-1, 0, 1, 1,-1,-1};
const int dy[] = {1,0, 0,-1, 1,-1, 1,-1};

inline bool inside(int x, int y) {
    return x >= 1 && x <= n && y <= x && y >= 1;
}

int main() {
    fin >> n >> d >> k;
    for(int i = 0 ; i < d ; ++ i) {
        fin >> queen[i].first >> queen[i].second;
        check[queen[i].first][queen[i].second] = 1;
    }
    for(int i = 0 ; i < k ; ++ i) {
        int x, y;
        fin >> x >> y;
        used[x][y] = 1;
    }
    int ans = 0;
    for(int i = n ; i >= 1 && !ans ; -- i) {
        bool okay = true;
        for(int j = 1 ; j <= i && okay ; ++ j)
            if(used[i][j])
                okay = false;
        if(okay)
            ans = i;
    }
    int checkers = 0;
    for(int i = 0 ;i < d ; ++ i) {
        cerr << i << ": ";
        for(int dir = 0 ; dir < 8 ; ++ dir) {
            int newx = queen[i].first + dx[dir];
            int newy = queen[i].second + dy[dir];
            while(inside(newx, newy) && !used[newx][newy]) {
                if(!check[newx][newy])
                    ++ checkers;
                check[newx][newy] = 1;
                newx = newx + dx[dir];
                newy = newy + dy[dir];
            }
        }
    }
    fout << ans << '\n';
    fout << checkers << '\n';
}
