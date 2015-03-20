#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <string.h>

using namespace std;

const char infile[] = "team.in";
const char outfile[] = "team.out";

ofstream fout(outfile);

const int MAXN = 505;
const int MAXP = 55;
const int oo = 0x3f3f3f3f;

typedef vector< pair<int, int> > Graph[MAXN];
typedef vector< pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;
int P, N, M, dest[MAXP], d[MAXN][MAXN], dp[MAXP][MAXP][MAXN];
queue<int> Q;
bitset<MAXN> inQ;

FILE* fin=fopen("team.in","r");
const unsigned maxb=8192;
char buf[maxb];
unsigned ptr=maxb;

inline unsigned getInt(){
    unsigned nr=0;
    while(buf[ptr]<'0'||'9'<buf[ptr])
            if(++ptr>=maxb)
                    fread(buf,maxb,1,fin),ptr=0;
    while('0'<=buf[ptr]&&buf[ptr]<='9'){
            nr=nr*10+buf[ptr]-'0';
            if(++ptr>=maxb)
                    fread(buf,maxb,1,fin),ptr=0;
    }
    return nr;
}

inline void BFs(int S, int best[]) {
    inQ.reset();

    Q.push(S);
    best[S] = 0;
    inQ[S] = true;

    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        inQ[Node] = false;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(best[it->first] > best[Node] + it->second) {
                best[it->first] = best[Node] + it->second;
                if(!inQ[it->first]){
                    Q.push(it->first);
                    inQ[it->first] = true;
                }
            }
    }
}

inline int Memo(const int i, const int j, const int k) {
    if(i > j)
        return 0;
    if(dp[i][j][k] != oo)
        return dp[i][j][k];
    if(i == j)
        return d[i][k];
    for(int l = i ; l <= j ; ++ l)
        Get_min(dp[i][j][k], d[l][k] + Memo(i, l-1, dest[l]) + Memo(l + 1, j, dest[l]));
    return dp[i][j][k];
}

int main() {
    P = getInt(); N = getInt(); M = getInt();
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        x = getInt(); y = getInt(); z = getInt();
        G[x].push_back(make_pair(y, z));
        G[y].push_back(make_pair(x, z));
    }
    for(int i = 1 ; i <= P ; ++ i)
        dest[i] = getInt();
    memset(d, oo, sizeof(d));
    for(int i = 1 ; i <= P ; ++ i)
        BFs(dest[i], d[i]);
    memset(dp, oo, sizeof(dp));
    fout << Memo(1, P, 1);
    fout.close();
    return 0;
}
