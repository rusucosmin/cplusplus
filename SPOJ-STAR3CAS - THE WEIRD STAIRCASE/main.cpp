#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <bitset>
#include <string.h>

using namespace std;

const int maxn = 105;

int dist[maxn], n, x[maxn], t;

inline void bfs(int stnode) {
    memset(dist, -1, sizeof(dist));
    queue<int> q;
    q.push(stnode);
    dist[stnode] = 0;
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        if(node == n)
            continue;
        if(dist[node + 1] == -1) {
            dist[node + 1] = dist[node] + 1;
            q.push(node + 1);
        }
        if(node + x[node] <= n && node + x[node] >= 0)
            if(dist[node + x[node]] == -1) {
                dist[node + x[node]] = dist[node] + 1;
                q.push(node + x[node]);
            }
    }
    cout << dist[n] << '\n';
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE
    cin >> t;
    while(t -- ) {
        cin >> n;
        for(int i = 0 ; i < n ; ++ i)
            cin >> x[i];
        bfs(0);
    }

}
