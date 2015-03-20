#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <string.h>
#include <cassert>
#include <set>

using namespace std;

const char infile[] = "easygraph.in";
const char outfile[] = "easygraph.out";

ifstream cin(infile);
ofstream cout(outfile);

const int MAXN = 15005;
const long long oo = 0x3f3f3f3f;

typedef set<int> Graph[MAXN];
typedef set<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;
int N, M;
long long v[MAXN];
long long Ans = -oo;
long long dp[MAXN];
bitset <MAXN> Used;

void DFs(const int &Node) {
    if(Used[Node])
        return;
    Used[Node] = true;
    long long aux = 0;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        DFs(*it);
        aux = max(aux, dp[*it]);
    }
    dp[Node] += aux;
    if(Ans < dp[Node])
        Ans = dp[Node];
}

inline void Read() {
    cin >> N >> M;
    for(int i = 1 ; i <= N ;  ++ i)
        cin >> v[i];
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        cin >> x >> y;
        if(G[x].find(y) == G[x].end())
            G[x].insert(y);
    }
    for(int i = 1 ; i <= N ; ++ i)
        dp[i] = v[i];
    for(int i = 1 ; i <= N ; ++ i)
        if(!Used[i])
            DFs(i);
    cout << Ans << '\n';
}

inline void Clear() {
    for(int i = 1 ; i <= N ; ++ i)
        G[i].clear();
    Used.reset();
    Ans = -oo;
}

int main() {
    int T;
    cin >> T;
    for(int t=1;t<=T;++t) {
        Read();
        Clear();
    }
    cin.close();
    cout.close();
    return 0;
}
