#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cassert>

using namespace std;

const char infile[] = "salvare.in";
const char outfile[] = "salvare.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int dp[MAXN], deg[MAXN], father[MAXN];
Graph g;
int N, K;
queue <int> Q;
vector <int> act, sol;
int level[MAXN], w[MAXN], helped[MAXN];

inline bool full() {
    for(int i = 1 ; i <= N ; ++ i)
        if(!helped[i])
            return false;
    return true;
}

inline void Help(int node, int dist) {
    if(!dist)
        return;
    helped[node] = dist;
    for(auto it:g[node])
        if(helped[it] < dist - 1)
            Help(it, dist - 1);
}

inline bool full2(int M) {
    memset(helped, 0, sizeof(helped));
    for(auto it:act)
        Help(it, M + 1);
    return full();
}

inline bool notOkay(int M) {
    vector <int>().swap(act);
    for(int i = 1 ; i <= N ; ++ i) {
        deg[i] = g[i].size();
        dp[i] = oo;
        if(deg[i] == 1) {
            Q.push(i);
            dp[i] = M;
        }
    }
    while(!Q.empty()) {
        int node = Q.front();
        Q.pop();
        deg[node] = 0;
        if(dp[node] == 0) {
            act.push_back(node);
            if(act.size() > K) {
                queue <int>().swap(Q);
                return false;
            }
            dp[node] = (M << 1) + 1;
        }
        for(It it = g[node].begin(), fin = g[node].end(); it != fin ; ++ it) {
            -- deg[*it];
            dp[*it] = min(dp[node] - 1, dp[*it]);
            if(deg[*it] == 1)
                Q.push(*it);
        }
    }
    return full2(M);
}

inline int getDad(int node, int where) {
    for(int i = 1 ; i <= where && father[node] ; ++ i)
        node = father[node];
    return node;
}

inline bool Okay(int M) {
    memset(helped, 0, sizeof(helped));
    int cnt = 0;
    vector <int>().swap(act);
    for(int i = 1 ; i <= N ; ++ i) {
        if(helped[w[i]])
            continue;
        int mDad = getDad(w[i], M);
        ++ cnt;
        act.push_back(mDad);
        Help(mDad, M + 1);
        if(act.size() > K)
            return false;
    }
    return full();
}

inline int getAns() {
    int li = 0, ls = N, ret = -1;
    while(li <= ls) {
        int mid = ((li + ls) >> 1);
        if(Okay(mid)) {
            ls = mid - 1;
            ret = mid;
            sol = act;
        }
        else
            li = mid + 1;
    }
    return ret;
}

inline int getAns2() {
    int li = 0, ls = N, ret = -1;
    while(li <= ls) {
        int mid = ((li + ls) >> 1);
        if(notOkay(mid)) {
            ls = mid - 1;
            ret = mid;
            sol = act;
        }
        else
            li = mid + 1;
    }
    return ret;
}

inline void dfs(int node) {
    level[node] = level[father[node]] + 1;
    for(It it = g[node].begin(); it != g[node].end(); ++ it)
        if(*it != father[node]) {
            father[*it] = node;
            dfs(*it);
        }
}

struct classComp {
    inline bool operator () (const int &a, const int &b) const {
        return level[a] > level[b];
    }
};

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    fin >> N >> K;
    for(int i = 1 ; i < N ; ++ i) {
        int x, y;
        fin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    int ans2 = getAns2();
    dfs(1);
    for(int i = 1 ; i <= N ; ++ i)
        w[i] = i;
    sort(w + 1, w + N + 1, classComp());

    int ans;
    fout << (ans = getAns()) << '\n';
    assert(ans != -1);
    assert(ans2 - ans <= 2);
    memset(deg, 0, sizeof(deg));

    ///fout << ans << '\n';
    for(int i = 0 ; i < sol.size() ; ++ i)
        deg[sol[i]] = 1;
    for(int i = 1 ; i <= N && sol.size() != K ; ++ i)
        if(!deg[i])
            sol.push_back(i);
    sort(sol.begin(), sol.end());
    for(auto it:sol)
        fout << it << ' ';
    fin.close();
    fout.close();
    return 0;
}
