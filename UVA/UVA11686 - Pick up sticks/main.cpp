#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <queue>

using namespace std;

const int maxn = 1000035;

vector <int> g[maxn];
int n, m, in[maxn];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE
    while(cin >> n >> m) {
        if(!n && !m)
            return 0;
        for(int i = 1 ; i <= m ; ++ i) {
            int x, y;
            cin >> x >> y;
            g[x].push_back(y);
            ++ in[y];
        }
        queue <int> q;
        for(int i = 1 ; i <= n ; ++ i)
            if(in[i] == 0)
                q.push(i);
        vector <int> tsort;
        while(!q.empty()) {
            int node = q.front();
            tsort.push_back(node);
            q.pop();
            for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it)
                if(-- in[*it] == 0)
                    q.push(*it);
        }
        if(tsort.size() != n)
            cout << "IMPOSSIBLE\n";
        else
            for(auto it : tsort)
                cout << it << '\n';
        for(int i = 1 ; i <= n ; ++ i) {
            vector <int>().swap(g[i]);
            in[i] = 0;
        }
    }

}
