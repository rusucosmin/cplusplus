///http://www.spoj.com/problems/BOTTOM/
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <bitset>

using namespace std;

const int maxn = 5005;

vector<int> g[maxn], gt[maxn], discovered;
int n, m, ans[maxn], where[maxn];
bitset <maxn> used;

inline void dfs(int node) {
    used[node] = 1;
    for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
        if(!used[*it])
            dfs(*it);
    discovered.push_back(node);
}

inline void scc(int node, int comp) {
    where[node] = comp;
    used[node] = 0;
    for(vector <int> :: iterator it = gt[node].begin() ; it != gt[node].end() ; ++ it)
        if(used[*it])
            scc(*it, comp);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("bottom.in", "r", stdin);
    freopen("bottom.out", "w", stdout);
    #endif // ONLINE_JUDGE
    cin.sync_with_stdio(false);
    while(true) {
        cin >> n >> m;
        if(n == 0)
            return 0;
        for(int i = 1 ; i <= m ; ++ i) {
            int x, y;
            cin >> x >> y;
            g[x].push_back(y);
            gt[y].push_back(x);
        }
        for(int i = 1 ; i <= n ; ++ i)
            if(!used[i])
                dfs(i);
        int comp = 0;
        for(vector <int> :: reverse_iterator it = discovered.rbegin() ; it != discovered.rend() ; ++ it)
            if(used[*it]) {
                scc(*it, ++ comp);
                ans[comp] = 1;
            }
        for(int i = 1 ; i <= n ; ++ i)
            for(vector <int> :: iterator it = g[i].begin() ; it != g[i].end() ; ++ it)
                if(where[i] != where[*it])
                    ans[where[i]] = 0;
        for(int i = 1 ; i <= n ; ++ i)
            if(ans[where[i]])
                cout << i << ' ';
        cout << '\n';
        for(int i = 1 ; i <= n ; ++ i) {
            vector <int>().swap(g[i]);
            vector <int>().swap(gt[i]);
        }
    }
}
