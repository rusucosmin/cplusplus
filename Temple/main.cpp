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
#include <stack>

using namespace std;

const char infile[] = "temple.in";
const char outfile[] = "temple.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const long long oo = 1000000000000005;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph g;
int N, v[MAXN], K, nxt[MAXN];
long long c[MAXN], arb[MAXN << 2], ans[MAXN];
vector <int> roots;

inline void Update(int node, int st, int dr, int pos, long long value) {
    if(st == dr) {
        arb[node] = value;
        return;
    }
    int mid = ((st + dr) >> 1);
    if(pos <= mid)
        Update(node << 1, st, mid, pos, value);
    else
        Update((node << 1) | 1, mid + 1, dr, pos, value);
    arb[node] = max(arb[node << 1], arb[(node << 1) | 1]);
}

inline long long Query(int node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b)
        return arb[node];
    int mid = ((st + dr) >> 1);
    long long ans = -oo;
    if(a <= mid)
        ans = max(ans, Query(node << 1, st, mid, a, b));
    if(mid < b)
        ans = max(ans, Query((node << 1) | 1, mid + 1, dr, a, b));
    return ans;
}

inline void dfs(int node, int actlevel) {
    Update(1, 1, N, actlevel, c[node]);
    //cerr << node << ' ' << max(1, actlevel - K + 1) << ' ' << actlevel << '\n';
    ans[node] = Query(1, 1, N, max(1, actlevel - K + 1), actlevel);
    for(auto it : g[node])
        if(node != it)
            dfs(it, actlevel + 1);
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    fin >> N >> K;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> v[i];
    for(int i = 1 ; i <= N ; ++ i)
        fin >> c[i];
    stack <int> st;
    for(int i = N ; i ; -- i) {
        while(!st.empty() && v[st.top()] <= v[i])
            st.pop();
        if(st.empty())
            nxt[i] = i;
        else
            nxt[i] = st.top();
        g[nxt[i]].push_back(i);
        if(nxt[i] == i)
            roots.push_back(i);
        st.push(i);
    }
    for(auto it : roots)
        dfs(it, 1);
    for(int i = 1 ; i <= N ; ++ i)
        fout << ans[i] << ' ';
    fin.close();
    fout.close();
    return 0;
}
