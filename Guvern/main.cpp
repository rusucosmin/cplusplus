#include <fstream>
#include <vector>
#include <bitset>
#include <set>
#include <stack>
#include <algorithm>
#include <cassert>
#include <string>

using namespace std;

const char infile[] = "guvern.in";
const char outfile[] = "guvern.out";

const int MAXN = 200005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, v[MAXN], First[MAXN], Last[MAXN], dp[MAXN], Ans, K;
Graph G, T;
set <pair<int, int> > S;

//<parsing>
FILE* fin=fopen("guvern.in","r");
const unsigned maxb=8192;
char buf[maxb];
unsigned ptr=maxb;

inline int getInt() {
    int nr=0;
    char semn='+';
    while(buf[ptr]<'0'||'9'<buf[ptr]) {
        semn = buf[ptr];
        if(++ptr>=maxb)
            fread(buf,maxb,1,fin),ptr=0;
    }
    while('0'<=buf[ptr]&&buf[ptr]<='9') {
        nr=nr*10+buf[ptr]-'0';
        if(++ptr>=maxb)
            fread(buf,maxb,1,fin),ptr=0;
    }
    if(semn == '-')
        nr = -nr;
    return nr;
}

inline void CatchDP(const int &Node) {
    stack <int> Stack, DP;
    for(It it = T[Node].begin(), fin = T[Node].end(); it != fin ; ++ it) {
        int candidate = *it, actDP = 0;
        while(!Stack.empty() && First[candidate] <= First[Stack.top()] && Last[Stack.top()] <= Last[candidate]) {
            actDP += DP.top();
            Stack.pop();
            DP.pop();
        }
        Stack.push(candidate);
        DP.push(max(actDP, dp[candidate]));
    }
    for(;!DP.empty() ; DP.pop())
        dp[Node] += DP.top();
    ++ dp[Node];
    Get_max(Ans, dp[Node]);
}

void DFs(const int &Node, const int &Father) {
    S.insert(make_pair(v[Node], Node));
    First[Node] = ++ K;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(*it == Father)
            continue;
        DFs(*it, Node);
    }
    Last[Node] = ++ K;
    S.erase(make_pair(v[Node], Node));
    set< pair<int, int> > :: iterator it = S.upper_bound(make_pair(v[Node], 0));
    if(it != S.end())
        T[it->second].push_back(Node);
    CatchDP(Node);
}

int main() {
    ofstream fout(outfile);
    N = getInt();
    for(int i = 1 ; i != N ; ++ i) {
        int x, y;
        x = getInt();
        y = getInt();
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for(int i = 1 ; i <= N ; ++ i)
        v[i] = getInt();
    G[0].push_back(1);
    v[0] = oo;
    DFs(0, -1);
    fout << Ans - 1 << '\n';
    fout.close();
    return 0;
}
