/*
    http://www.spoj.com/problems/SHPATH/
*/
#include <iostream>
#include <fstream>
#include <string.h>
#include <map>
#include <queue>
#include <cassert>
#include <vector>

using namespace std;

const int maxn = 10005;
const int oo = 0x3f3f3f3f;

vector <pair<int, int> > g[maxn];
int t, n, dist[maxn];
map<string, int> idx;
priority_queue <pair<int, int> > q;

inline int dijkstra(int stnode, int fnnode) {
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
    assert(dist[fnnode] != oo);
    return dist[fnnode];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("shpath.in", "r", stdin);
    freopen("shpath.out", "w", stdout);
    #endif // ONLINE_JUDGE
    cin.sync_with_stdio(false);
    cin >> t;
    while(t -- ) {
        cin >> n;
        idx.clear();
        for(int i = 1 ; i <= n ; ++ i) {
            vector <pair<int, int> > ().swap(g[i]);
            string s;
            cin >> s;
            idx[s] = i;
            int x;
            cin >> x;
            for(int j = 1 ; j <= x ; ++ j) {
                int y, z;
                cin >> y >> z;
                g[i].push_back(make_pair(y, z));
               // g[y].push_back(make_pair(x, z));
            }
        }
        int m;
        cin >> m;
        for(int i = 1 ; i <= m ; ++ i) {
            string a, b;
            cin >> a >> b;
            cout << dijkstra(idx[a], idx[b]) << '\n';
        }
    }
    return 0;
}
