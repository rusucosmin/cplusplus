#include <iostream>
#include <fstream>
#include <string.h>
#include <queue>

using namespace std;

const int maxn = 1005;

const int dx[] = {0, 1, -1, 0};
const int dy[] = {1, 0,  0,-1};

int n, m, dist[maxn][maxn];
char s[maxn][maxn];

inline bool inside(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m && s[x][y] == '.';
}

inline pair<int, int> bfs(int stx, int sty) {
    memset(dist, -1, sizeof(dist));
    queue <pair<int, int> > q;
    q.push(make_pair(stx, sty));
    dist[stx][sty] = 0;
    pair<int, int> ret;
    while(!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        ret = q.front();
        q.pop();
        for(int i = 0 ; i < 4 ; ++ i) {
            int newx = x + dx[i];
            int newy = y + dy[i];
            if(inside(newx, newy) && dist[newx][newy] == -1) {
                dist[newx][newy] = dist[x][y] + 1;
                q.push(make_pair(newx, newy));
            }
        }
    }
    return ret;
}

int main() {
    int t;
    cin >> t;
    for(int test = 1 ; test <= t ; ++ test) {
        cin >> m >> n;
        for(int i = 1 ; i <= n ; ++ i)
            cin >> s[i] + 1;
        pair<int, int> ans;
        bool okay = false;
        for(int i = 1 ; i <= n && !okay ; ++ i)
            for(int j = 1 ; j <= m && !okay ; ++ j)
                if(s[i][j] == '.') {
                    ans = make_pair(i, j);
                    okay = true;
                }
        ans = bfs(ans.first, ans.second);
        ans = bfs(ans.first, ans.second);
        cout << "Maximum rope length is " << dist[ans.first][ans.second] << ".\n";
    }
}
