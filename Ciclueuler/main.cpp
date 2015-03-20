#include <iostream>
#include <vector>
#include <bitset>
#include <stack>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream fin("ciclueuler.in");
ofstream fout("ciclueuler.out");

const int maxn = 100005;

vector <int> g[maxn];
bitset <maxn> used;
int n, m;

inline void dfs(int node) {
    used[node] = 1;
    for(auto it : g[node])
        if(!used[it])
            dfs(it);
}

inline void euler(int stnode) {
    stack <int> st;
    st.push(stnode);
    vector <int> cycle;
    while(!st.empty()) {
        int node = st.top();
        if(g[node].size()) {
            int newnode = g[node].back();
            g[node].pop_back();
            g[newnode].erase(find(g[newnode].begin(), g[newnode].end(), node));
            st.push(newnode);
        }
        else {
            st.pop();
            if(!st.empty())
                cycle.push_back(node);
        }
    }
    for(auto it : cycle)
        fout << it << ' ';
}

int main() {
    fin >> n >> m;
    for(int i = 1 ; i <= m ; ++ i) {
        int x, y;
        fin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(1);
    for(int i = 1 ; i <= n ; ++ i)
        if(!used[i] || (g[i].size() % 2 == 1)) {
            fout << "-1\n";
            return 0;
        }
    euler(1);
}
