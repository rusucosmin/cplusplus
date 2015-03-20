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

const char infile[] = "input.in";
const char outfile[] = "output.out";

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

bool G[MAXN][MAXN];
int N, M, K, deg[MAXN], cnt[MAXN];
bitset <MAXN> Used;

void Remove(const int &Node) {
    deg[Node] = 0;
    for(int i = 1 ;  i <= N ; ++ i)
        if(G[Node][i]) {
            G[Node][i] = 0;
            G[i][Node] = 0;
            -- deg[i];
            if(deg[i] > 0 && deg[i] < K)
                Remove(i);
        }
}

void DFs(const int &Node, const int &actComp) {
    ++ cnt[actComp];
    Used[Node] = true;
    for(int i = 1 ; i <= N ; ++ i)
        if(G[Node][i] && !Used[i])
            DFs(i, actComp);
}

#define fin cin
#define fout cout

int main() {
    cin.sync_with_stdio(false);
    while(fin >> N >> M >> K) {
        if(!N && !M && !K)
            return 0;
        memset(G, 0, sizeof(G));
        memset(deg, 0, sizeof(deg));
        memset(cnt, 0, sizeof(cnt));
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y;
            fin >> x >> y;
            G[x][y] = 1;
            G[y][x] = 1;
            ++ deg[x];
            ++ deg[y];
        }
        for(int i = 1 ; i <= N ; ++ i)
            if(deg[i] > 0 && deg[i] < K)
                Remove(i);
        Used.reset();
        int ctc = 0;
        int Ans = 0;
        for(int i = 1 ; i <= N ; ++ i)
            if(deg[i] > 0 && !Used[i]) {
                DFs(i, ++ ctc);
                Ans = max(Ans, cnt[ctc]);
            }
        fout << Ans << '\n';
    }
    return 0;
}
