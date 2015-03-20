#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>
#include <queue>
#include <string.h>

using namespace std;

const int maxn = 100005;

ifstream fin("bfs.in");
ofstream fout("bfs.out");

int n, m, s, dist[maxn];
vector <int> g[maxn];

inline void bfs(int s) {
    queue <int> q;
    memset(dist, -1, sizeof(dist));
    dist[s] = 0;
    q.push(s);
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        for(auto it : g[node])
            if(dist[it] == -1) {
                dist[it] = dist[node] + 1;
                q.push(it);
            }
    }
    for(int i = 1 ; i <= n ; ++ i)
        fout << dist[i] << ' ';
}

int main() {
    fin >> n >> m >> s;
    for(int i = 1 ; i <= m ; ++ i) {
        int x, y;
        fin >> x >> y;
        g[x].push_back(y);
    }
    bfs(s);
}
