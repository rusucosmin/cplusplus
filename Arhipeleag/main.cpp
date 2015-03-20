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
#include <deque>

using namespace std;

const char infile[] = "arhipelag.in";
const char outfile[] = "arhipelag.out";

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

const int lim = (1 << 20);
char buff[lim];
int pos;

inline void getInt(int &x) {
    x = 0;
    while(!('0' <= buff[pos] && buff[pos] <= '9'))
        if(++  pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    while('0' <= buff[pos] && buff[pos] <= '9') {
        x = x * 10 + buff[pos] - '0';
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }
}

int T, N, M, K;
Graph g;
bitset <MAXN> used;
int comp;
vector<int> cc;
int ans[105];
int many[MAXN];

inline void dfs(int node) {
    used[node] = true;
    ++ comp;
    for(It it = g[node].begin(), fin = g[node].end(); it != fin ; ++ it)
        if(!used[*it])
            dfs(*it);
}

int main() {
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);

    getInt(T);
    for(int test = 1 ; test <= T ; ++ test) {
        getInt(N);
        getInt(M);
        getInt(K);
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y;
            getInt(x);
            getInt(y);
            g[x].push_back(y);
            g[y].push_back(x);
        }
        for(int i = 1 ; i <= N ; ++ i)
            if(!used[i]) {
                comp = 0;
                dfs(i);
                cc.push_back(comp);
            }
        sort(cc.rbegin(), cc.rend());
        memset(many, 0, sizeof(many));
        memset(ans, 0, sizeof(ans));
        for(int i = 0 ; i < cc.size() ; ++ i)
            many[i % K] += cc[i];
        for(int i = 0 ; i < K ; ++ i) {
            int x;
            getInt(x);
            ans[x] = many[i];
        }
        printf("Case %d:", test);
        for(int i = 1 ; i <= K ; ++ i)
            printf(" %d", ans[i]);
        printf("\n");
        for(int i = 1 ; i <= N ; ++ i)
            vector<int>().swap(g[i]);
        used.reset();
        vector<int>().swap(cc);
    }
    return 0;
}
