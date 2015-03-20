#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <queue>
#include <string.h>

using namespace std;

ifstream fin("ubuntzei.in");
ofstream fout("ubuntzei.out");

const int maxn = 2005;
const int maxk = 17;
const int oo = 0x3f3f3f3f;

int n, m, k,len[maxk][maxk], dist[maxn], dp[1 << maxk][maxk];
vector <pair<int, int> > g[maxn];
vector <int> s;

inline void dijkstra(int stnode) {
    priority_queue<pair<int, int> > q;
    memset(dist, oo, sizeof(dist));
    dist[stnode] = 0;
    q.push(make_pair(0, stnode));
    while(!q.empty()) {
        int node = q.top().second;
        int cost = -q.top().first;
        q.pop();
        if(dist[node] < cost)
            continue;
        for(vector <pair<int, int> > :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
            if(dist[it->first] > cost + it->second) {
                dist[it->first] = cost + it->second;
                q.push(make_pair(-dist[it->first], it->first));
            }
    }
}

int main() {
    fin >> n >> m;
    fin >> k;
    s.push_back(0);
    for(int i = 1 ; i <= k ; ++ i) {
        int x;
        fin >> x;
        -- x;
        s.push_back(x);
    }
    s.push_back(n - 1);
    for(int i = 1 ; i <= m ; ++ i) {
        int x, y, z;
        fin >> x >> y >> z;
        -- x;
        -- y;
        g[x].push_back(make_pair(y, z));
        g[y].push_back(make_pair(x, z));
    }
    for(int i = 0 ; i < s.size() ; ++ i) {
        dijkstra(s[i]);
        for(int j = 0 ; j < s.size() ; ++ j)
            len[i][j] = dist[s[j]];
    }
    memset(dp, oo, sizeof(dp));
    dp[1][0] = 0;
    int maxmask = (1 << (s.size()));
    for(int mask = 1 ; mask < maxmask ; ++ mask) {
        for(int i = 0 ; i < s.size() ; ++ i)
            if(mask & (1 << i))
                for(int j = 0 ; j < s.size() ; ++ j)
                    if(mask & (1 << j))
                        dp[mask][i] = min(dp[mask][i], dp[mask ^ (1 << i)][j] + len[j][i]);
    }
    fout << dp[maxmask - 1][s.size() - 1] << '\n';
}
