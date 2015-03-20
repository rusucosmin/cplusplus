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

const char infile[] = "import.in";
const char outfile[] = "import.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 225;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph Tree;
int S[MAXN], N, M, K;
int P[MAXN], G[MAXN][MAXN];

inline void bellmanFord(void) {
    S[0] = 0;
    for(int i = 0 ; i <= N ; ++ i)
        for(int j = 0 ; j <= N ; ++ j)
            for(int k = 0 ; k <= N ; ++ k)
                if(S[k] > S[j] + G[j][k])
                    S[k] = S[j] + G[j][k];
    for(int i = 0 ; i <= N ; ++ i)
        for(int j = 0 ; j <= N ; ++ j)
            if(S[j] > S[i] + G[i][j]) {
                fout << "No solution\n";
                exit(0);
            }
}

inline void DFs(const int &Node, const int &Father) {
    if(Node > K && Father == 1)
        P[Node] = S[Node];
        else if(Node != 1)
            P[Node] = S[Node] - S[Father];
    for(It it = Tree[Node].begin(), fin = Tree[Node].end(); it != fin ; ++ it)
        if(*it != Father)
            DFs(*it, Node);
}

int main() {
    fin >> N >> M >> K;
    for(int i = 1 ; i != N ; ++ i) {
        int x, y;
        fin >> x >> y;
        Tree[x].push_back(y);
        Tree[y].push_back(x);
    }
    memset(G, 1, sizeof(G));
    for(int i = 1 ; i <= N ; ++ i)
        G[0][i] = 0;
    for(int i = 1 ; i <= M ; ++ i) {
        int a, b, c, d;
        fin >> a >> b >> c >> d;
        if(d == 0)
            G[b][a] = -c;
        else G[a][b] = c - 1;
    }
    bellmanFord();
    for(int i = K + 1 ; i <= N ; ++ i)
        S[i] = -S[i];
    P[1] = S[1];
    DFs(1, -1);
    for(int i = 1 ; i <= N ; ++ i)
        fout << P[i] << ' ';
    fin.close();
    fout.close();
    return 0;
}
