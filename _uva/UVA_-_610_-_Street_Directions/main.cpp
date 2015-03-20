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

int depth[MAXN], lowlink[MAXN];
int G[MAXN][MAXN];
int N, M;

void DFs(int Node, int Father, int actLevel) {
    lowlink[Node] = depth[Node] = actLevel;
    for(int i = 1 ; i <= N ; ++ i) {
        if(G[Node][i]) {
            if(i == Father)
                continue;
            if(!depth[i]) {
                DFs(i, Node, actLevel + 1);
                lowlink[Node] = min(lowlink[Node], lowlink[i]);
                if(lowlink[i] <= depth[Node])
                    G[i][Node] = 0;
            }
            else {
                lowlink[Node] = min(lowlink[Node], depth[i]);
                G[i][Node] = 0;
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    cin.sync_with_stdio(false);
    #endif
    int test = 0;
    while(cin >> N >> M) {
        if(!N && !M)
            return 0;
        memset(G, 0, sizeof(G));
        memset(depth, 0, sizeof(depth));
        memset(lowlink, 0, sizeof(lowlink));
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y;
            cin >> x >> y;
            G[x][y] = 1;
            G[y][x] = 1;
        }
        DFs(1, 1, 1);
        cout << ++ test << "\n\n";
        for(int i = 1 ; i <= N ; ++ i)
            for(int j = 1 ; j <= N ; ++ j)
                if(G[i][j])
                    cout << i << ' ' << j << '\n';
        cout << "#\n";
    }
    return 0;
}
